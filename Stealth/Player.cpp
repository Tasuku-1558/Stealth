#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "InputManager.h"

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="inEffect">エフェクトマネージャーのポインタ</param>
/// <param name="inMapHit">マップと衝突したかどうか</param>
/// <param name="inPushBack">プレイヤーへの押し戻し量</param>
Player::Player(EffectManager* const inEffect, bool inMapHit, VECTOR inPushBack)
{
	effectManager = inEffect;

	mapHit = inMapHit;

	pushBack = inPushBack;

	Initialize();
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

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		//プレイヤー残像モデルの読み込み
		afterImageModel[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

		//モデルの不透明度の設定
		//0.0fに近いほど透明度が上がる
		MV1SetOpacityRate(afterImageModel[i], OPACITY);

		//モデルのエミッシブカラーを変更
		MV1SetMaterialEmiColor(afterImageModel[i], MATERIAL_INDEX, AFTER_IMAGE_COLOR);

		pastPosition[i] = POSITION;
	}

	//見つかった画像の読み込み
	playerFindImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());

	position = POSITION;
	nextPosition = POSITION;

	direction = DIRECTION;
	speed = SPEED;

	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = POSITION;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DeleteModel(afterImageModel[i]);
	}

	DeleteGraph(playerFindImage);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	AfterImage();
}

/// <summary>
/// キー入力処理
/// </summary>
void Player::KeyInput()
{
	Key key[] =
	{
		{KEY_INPUT_W, UP},
		{KEY_INPUT_S, DOWN},
		{KEY_INPUT_D, RIGHT},
		{KEY_INPUT_A, LEFT},
	};

	for (int i = 0; i < KEY_INPUT_PATTERN; i++)
	{
		if (KeyManager::GetInstance().CheckPressed(key[i].input))
		{
			inputDirection += key[i].dir;
			inputFlag = true;
		}
	}
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Player::Move(float deltaTime)
{
	//入力方向を初期化する
	inputDirection = ZERO_VECTOR;

	KeyInput();

	//キーの入力があったら
	if (inputFlag)
	{
		//左右・上下同時押しなどで入力ベクトルが0の時は移動できない
		if (VSize(inputDirection) < MAX_INPUT_DIRECTION)
		{
			return;
		}

		//キーの入力方向を正規化
		direction = VNorm(inputDirection);
		
		//キーの移動方向に移動
		nextPosition += direction * speed * deltaTime;

		HitMap();
	}

	//モデルの位置と向きを設定
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, direction, Y_ANGLE);

	//当たり判定球の移動処理
	collisionSphere.Move(position);
}

/// <summary>
/// マップに衝突したかどうか
/// </summary>
void Player::HitMap()
{
	//マップにプレイヤーが衝突したならば
	if (mapHit)
	{
		//未来の位置に押し戻しの値を加える
		nextPosition = pushBack;

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
		MV1SetPosition(afterImageModel[i], pastPosition[i] - AFTER_IMAGE_ADJUSTMENT);
		MV1SetRotationYUseDir(afterImageModel[i], direction, Y_ANGLE);

		pastPosition[0] = position;
		MV1SetPosition(afterImageModel[0], pastPosition[0] - AFTER_IMAGE_ADJUSTMENT);
		MV1SetRotationYUseDir(afterImageModel[0], direction, Y_ANGLE);
	}
}

/// <summary>
/// エネミーに見つかった場合
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
/// <param name="spotted">エネミーに見つかったかどうか</param>
void Player::FoundEnemy(float deltaTime, bool spotted)
{
	//エネミーに見つかったら
	if (spotted)
	{
		//プレイヤーの動きを止める
		speed = STOP_SPEED;

		//エネミーに見つかった時の画像を表示
		findImageFlag = true;

		//初期位置に戻すカウントを開始する
		initialTime += deltaTime;

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
	if (initialTime > MAX_INITIAL_TIME)
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

		initialTime = INITIAL_TIME;

		//エネミーに見つかった回数を1プラスする
		playerFindCount++;

		findImageFlag = false;
		spottedSeFlag = false;

		//リスポーンエフェクトを出す
		effectManager->CreateEffect(position, EffectManager::RESPAWN);
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
		DrawGraph(FIND_IMAGE_X, FIND_IMAGE_Y, playerFindImage, TRUE);
	}

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(afterImageModel[i]);
	}

	MV1DrawModel(modelHandle);
}