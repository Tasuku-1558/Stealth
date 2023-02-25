#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "KeyManager.h"

using namespace Math3d;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() : PlayerBase()
	, initialCount(0.0f)
	, pastPosition()
	, emptyModel()
	, SOUND_FOLDER_PATH("data/sound/")
	, IMAGE_FOLDER_PATH("data/image/")
	, PLAYER_FIND_PATH("playerFind.png")
	, SPOTTED_SE_PATH("spotted.mp3")
	, AFTER_IMAGE_NUMBER(12)
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
		MV1SetOpacityRate(emptyModel[i], 0.05f);
		MV1SetMaterialEmiColor(emptyModel[i], 0, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
	}

	playerFindImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());

	spottedSe = LoadSoundMem(InputPath(SOUND_FOLDER_PATH, SPOTTED_SE_PATH).c_str());
}

/// <summary>
/// パスの入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string Player::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DeleteModel(emptyModel[i]);
	}

	DeleteGraph(playerFindImage);

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
		pastPosition[i] = position;
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

	AfterImage();
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
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_W))
	{
		inputDirection += camera->GetUp();
		inputFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += camera->GetDown();
		inputFlag = true;
	}
	//左右
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
	{
		inputDirection += camera->GetRight();
		inputFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
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

		//マップに衝突した
		HitMap(back, mapHit);
	}

	//モデルの位置と向きを設定
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, dir, 0.0f);
}

/// <summary>
/// マップに衝突した
/// </summary>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::HitMap(VECTOR back, bool mapHit)
{
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

/// <summary>
/// プレイヤーの残像処理
/// </summary>
void Player::AfterImage()
{
	for (int i = 11; i >= 1; i--)
	{
		pastPosition[i] = pastPosition[i - 1];
		MV1SetPosition(emptyModel[i], pastPosition[i] - VGet(0.0f, 10.0f, 0.0f));
	}

	pastPosition[0] = position;
	MV1SetPosition(emptyModel[0], pastPosition[0] - VGet(0.0f, 10.0f, 0.0f));

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1SetRotationYUseDir(emptyModel[i], dir, 0.0f);
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
		//プレイヤーの動きを止める
		speed = 0.0f;

		//エネミーに見つかった時の画像を表示
		findImageFlag = true;

		//初期位置に戻すカウントを開始する
		initialCount += deltaTime;

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

		for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
		{
			pastPosition[i] = position;
		}

		dir = DIR;
		speed = SPEED;

		playerFindCount++;
		initialCount = 0.0f;
		findImageFlag = false;
		spottedSeFlag = false;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	//エネミーに見つかったならば
	if (findImageFlag)
	{
		//見つかったという画像を描画
		DrawGraph(50, -100, playerFindImage, TRUE);
	}

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(emptyModel[i]);
	}

	MV1DrawModel(modelHandle);
}