#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="inEffect"></param>
Player::Player(EffectManager* const inEffect)
	: PlayerBase()
	, initialCount(0.0f)
	, pastPosition()
	, afterImageModelHandle()
	, IMAGE_FOLDER_PATH("Data/image/")
	, PLAYER_FIND_PATH("playerFind.png")
	, AFTER_IMAGE_NUMBER(12)
{
	effectManager = inEffect;

	Initialize();
	Activate();
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
	//プレイヤーモデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	//残像の枚数分読み込む
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		//プレイヤー残像モデルの読み込み
		afterImageModelHandle[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

		//モデルの不透明度の設定
		//0.0fに近いほど透明度が上がる
		MV1SetOpacityRate(afterImageModelHandle[i], OPACITY);

		//モデルのエミッシブカラーを変更
		MV1SetMaterialEmiColor(afterImageModelHandle[i], 0, AFTER_IMAGE_COLOR);
	}

	//画像の読み込み
	playerFindImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());
}

/// <summary>
/// パスの入力
/// </summary>
/// <param name="folderPath">画像フォルダーのパス</param>
/// <param name="path">画像のパス</param>
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
		MV1DeleteModel(afterImageModelHandle[i]);
	}

	DeleteGraph(playerFindImage);
}

/// <summary>
/// 活性化処理
/// </summary>
void Player::Activate()
{
	position = POSITION;
	nextPosition = POSITION;

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		pastPosition[i] = POSITION;
	}

	direction = DIRECTION;
	speed = SPEED;

	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Update(float deltaTime, VECTOR back, bool mapHit)
{
	Move(deltaTime, back, mapHit);

	AfterImage();

	//当たり判定球の移動処理
	collisionSphere.Move(position);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Move(float deltaTime, VECTOR back, bool mapHit)
{
	//入力方向を初期化する
	inputDirection = ZERO_VECTOR;

	//上下移動
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_W))
	{
		inputDirection += UP;
		inputFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += DOWN;
		inputFlag = true;
	}
	//左右移動
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
	{
		inputDirection += RIGHT;
		inputFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
	{
		inputDirection += LEFT;
		inputFlag = true;
	}

	//十字キーの入力があったら
	if (inputFlag)
	{

		//左右・上下同時押しなどで入力ベクトルが0の時は移動できない
		if (VSize(inputDirection) < 1.0f)
		{
			return;
		}

		//十字キーの入力方向を正規化
		direction = VNorm(inputDirection);
		
		//十字キーの移動方向に移動
		nextPosition += direction * speed * deltaTime;

		//マップに衝突した
		HitMap(back, mapHit);
	}

	//モデルの位置と向きを設定
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
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
		nextPosition = back;

		position = nextPosition;
		nextPosition = position;
	}
	else
	{
		position = nextPosition;
		nextPosition = position;
	}
}

/// <summary>
/// プレイヤーの残像処理
/// </summary>
void Player::AfterImage()
{
	for (int i = AFTER_IMAGE_NUMBER - 1; i >= 1; i--)
	{
		pastPosition[i] = pastPosition[i - 1];
		MV1SetPosition(afterImageModelHandle[i], pastPosition[i] - AFTER_IMAGE_ADJUSTMENT);
		MV1SetRotationYUseDir(afterImageModelHandle[i], direction, 0.0f);
	}

	pastPosition[0] = position;
	MV1SetPosition(afterImageModelHandle[0], pastPosition[0] - AFTER_IMAGE_ADJUSTMENT);
	MV1SetRotationYUseDir(afterImageModelHandle[0], direction, 0.0f);
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
			SoundManager::GetInstance().SePlayFlag(SoundManager::ENEMY_FIND);

			spottedSeFlag = true;
		}

		FoundCount();
	}
}

/// <summary>
/// エネミーに見つかった時の初期位置へ戻すカウント
/// </summary>
void Player::FoundCount()
{
	//初期化カウントが0.8秒経過したら
	if (initialCount > initialTime)
	{
		//位置と向きを初期位置に
		//スピードを元に戻す
		position = POSITION;
		nextPosition = POSITION;
		inputFlag = false;

		for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
		{
			pastPosition[i] = POSITION;
		}

		direction = DIRECTION;

		speed = SPEED;

		initialCount = 0.0f;

		//エネミーに見つかった回数を1プラスする
		playerFindCount++;

		findImageFlag = false;
		spottedSeFlag = false;

		//リスポーンエフェクトを出す
		effectManager->CreateRepopEffect(position);
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
		DrawGraph(findImageX, findImageY, playerFindImage, TRUE);
	}

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(afterImageModelHandle[i]);
	}

	MV1DrawModel(modelHandle);
}