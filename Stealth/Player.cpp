#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "Enemy.h"

const string Player::SOUND_FOLDER_PATH = "data/sound/";		//soundフォルダまでのパス
const string Player::SPOTTED_SE_PATH   = "spotted.mp3";		//エネミーに見つかった時のSE音のパス

using namespace Math3d;
using namespace std;


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() : PlayerBase()
	, count(0)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	//終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

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
	modelHandle = NULL;

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
}

/// <summary>
/// エネミーに見つかった場合
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="enemy"></param>
void Player::FoundEnemy(float deltaTime, Enemy* enemy)
{
	//エネミーに見つかったら
	if (enemy->Spotted())
	{
		count += deltaTime;

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
	if (count > 0.6f)
	{
		//位置と向きを初期位置に
		//スピードを元に戻す
		position = POSITION;
		previewPosition = POSITION;
		dir = DIR;
		speed = SPEED;

		playerFindCount++;
		count = 0.0f;
		spottedSeFlag = false;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{	
	MV1DrawModel(modelHandle);
}