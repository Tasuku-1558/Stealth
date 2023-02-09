#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const string Player::SOUND_FOLDER_PATH  = "data/sound/";		//soundフォルダまでのパス
const string Player::SPOTTED_SE_PATH    = "spotted.mp3";		//エネミーに見つかった時のSE音のパス
const int	 Player::AFTER_IMAGE_NUMBER = 3;					//プレイヤーの残像枚数

using namespace Math3d;
using namespace std;


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() : PlayerBase()
	, initialCount(0.0f)
	, pastPosition()
	, emptyModel()
	, count(0.0f)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	//プレイヤーモデル
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	//プレイヤー残像モデル
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		emptyModel[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
		MV1SetOpacityRate(emptyModel[i], 0.3f);
		MV1SetMaterialEmiColor(emptyModel[i], 0, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
	}

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[PLAYER]\n");
	}

	//SE音の読み込み
	string failePath = SOUND_FOLDER_PATH + SPOTTED_SE_PATH;
	spottedSe = LoadSoundMem(failePath.c_str());
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);

	//サウンドリソースを削除
	InitSoundMem();
}

/// <summary>
/// 活性化処理
/// </summary>
void Player::Activate()
{
	position = POSITION;
	previewPosition = POSITION;

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		pastPosition[i] = POSITION;
	}

	dir = DIR;
	speed = SPEED;
	playerFindCount = 0;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Update(float deltaTime, Camera* camera, VECTOR back, bool mapHit)
{
	Move(deltaTime, camera, back, mapHit);

	MV1SetPosition(modelHandle, position);

	AfterImage(deltaTime);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	//上下
	if (CheckHitKey(KEY_INPUT_W))
	{
		inputDirection += camera->GetUp();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		inputDirection += camera->GetDown();
		inputFlag = true;
	}
	//左右
	if (CheckHitKey(KEY_INPUT_D))
	{
		inputDirection += camera->GetRight();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		inputDirection += camera->GetLeft();
		inputFlag = true;
	}

	//十字キーの入力があったら
	if (inputFlag)
	{

		// 左右・上下同時押しなどで入力ベクトルが0の時
		if (VSquareSize(inputDirection) < 0.5f)
		{
			return;
		}

		//十字キーの入力方向を正規化
		inputDirection = VNorm(inputDirection);

		//十字キーの入力方向をキャラの向きとする
		dir = inputDirection;
		
		//十字キーの移動方向に移動
		previewPosition += dir * speed * deltaTime;

		//マップにプレイヤーが衝突したならば
		if (mapHit)
		{
			//未来の位置に押し戻しの値を加える
			previewPosition = back;

			position = previewPosition;
			previewPosition = position;
		}
		else
		{
			position = previewPosition;
			previewPosition = position;
		}
	}

	//z軸が逆を向いているのでdirを180度回転させる
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//モデルに回転をセット dirを向く
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1SetRotationZYAxis(emptyModel[i], negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	}

}

/// <summary>
/// プレイヤーの残像
/// </summary>
/// <param name="deltaTime"></param>
void Player::AfterImage(float deltaTime)
{
	count += deltaTime;

	if (count > 0.1f)
	{
		pastPosition[0] = position;

		MV1SetPosition(emptyModel[0], pastPosition[0]);

		if (count > 0.2f)
		{
			pastPosition[1] = pastPosition[0];

			MV1SetPosition(emptyModel[1], pastPosition[1]);

			if (count > 0.3f)
			{
				pastPosition[2] = pastPosition[1];

				MV1SetPosition(emptyModel[2], pastPosition[2]);

				count = 0.0f;
			}
		}
	}
}

/// <summary>
/// エネミーに見つかった場合
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="spotted"></param>
void Player::FoundEnemy(float deltaTime, bool spotted)
{
	//エネミーに見つかったら
	if (spotted)
	{
		//初期位置に戻すカウントを開始する
		initialCount += deltaTime;

		//プレイヤーの動きを止める
		speed = 0.0f;

		//一度だけサウンドを流す
		if (!spottedSeFlag)
		{
			//エネミーに見つかった時のSE音を再生
			PlaySoundMem(spottedSe, DX_PLAYTYPE_BACK);

			spottedSeFlag = true;
		}
	}

	//カウントが0.6秒経過したら
	if (initialCount > 0.6f)
	{
		//位置と向きを初期位置に
		//スピードを元に戻す
		position = POSITION;
		previewPosition = POSITION;
		dir = DIR;
		speed = SPEED;

		playerFindCount++;
		initialCount = 0.0f;
		spottedSeFlag = false;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(emptyModel[i]);
	}

	MV1DrawModel(modelHandle);
}