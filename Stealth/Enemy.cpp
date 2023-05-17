#include "Enemy.h"
#include "ModelManager.h"
#include "InputManager.h"

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="movePattern">行動パターンの番号</param>
/// <param name="enemySpeed">エネミーのスピード</param>
Enemy::Enemy(int movePattern, float enemySpeed)
	: enemyReaction(EnemyReaction::NORMAL)
	, cakeCount(0.0f)
	, cakeFindFlag(false)
	, rotateFlag(false)
	, cakeEat(false)
	, nextDirection()
	, IMAGE_FOLDER_PATH("Data/Image/")
	, MARK_PATH("mark.png")
{
	Position(GetList(movePattern));

	changeSpeed = enemySpeed;

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize()
{
	//エネミーモデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	//視野モデルの読み込み
	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//ビックリマーク画像の読み込み
	markImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());

	speed = changeSpeed;

	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// エネミー位置設定
/// </summary>
/// <param name="id">敵の行動パターンリスト</param>
void Enemy::Position(vector<VECTOR>& id)
{
	pointList = id;					//座標リストを受け取る

	itr = pointList.begin();		//イテレータを先頭に設定

	position = *itr++;				//イテレータから敵座標を設定

	enemyState = EnemyState::ARRIVAL;
}

/// <summary>
/// 終了処理
/// </summary>
void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(visualModelHandle);

	DeleteGraph(markImage);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
/// <param name="playerPosition">プレイヤーの座標</param>
void Enemy::Update(float deltaTime, VECTOR playerPosition)
{
	StateUpdate(deltaTime);

	Move(deltaTime);

	VisualAnglePlayer(playerPosition);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Enemy::Move(float deltaTime)
{
	if (enemyState == EnemyState::CRAWL || enemyState == EnemyState::ARRIVAL)
	{
		//現在の向き
		direction = VNorm(targetPosition - position);
	}
	
	if (enemyState == EnemyState::ROTATION)
	{
		//現在の向き
		direction = VNorm(direction);

		//目標の向き
		nextDirection = VNorm(targetPosition - position);
	}

	position += direction * speed * deltaTime;

	//エネミーの位置と向きをセット
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, direction, Y_ANGLE);

	//視野の位置と向きをセット
	MV1SetPosition(visualModelHandle, position);
	MV1SetRotationYUseDir(visualModelHandle, direction, Y_ANGLE);

	//当たり判定球の移動処理
	collisionSphere.Move(position);
}

/// <summary>
/// 目的地まで移動処理
/// </summary>
void Enemy::SetTargetPosition()
{
	targetPosition = *itr++;

	//最終目的地に到着したら次の目的地に向かう
	if (itr == pointList.end())
	{
		itr = pointList.begin();
	}

	enemyState = EnemyState::CRAWL;
}

/// <summary>
/// 目的地に到達したならば
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
/// <returns></returns>
bool Enemy::IsGoal(float deltaTime)
{
	return VSize(targetPosition - position) < speed * deltaTime;
}

/// <summary>
/// エネミーの回転処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Enemy::EnemyRotate(float deltaTime)
{
	//エネミーを回転させるか
	if (rotateFlag)
	{
		//回転が目標角度に十分近ければ回転をやめる
		if (IsNearAngle(nextDirection, direction))
		{
			direction = nextDirection;
			rotateFlag = false;
		}
		else
		{
			//回転させる
			VECTOR interPolateDir = RotateForAimVecYAxis(direction, nextDirection, Y_ANGLE_SPEED);

			//回転が目標角度を超えていないか
			VECTOR cross1 = VCross(direction, nextDirection);
			VECTOR cross2 = VCross(interPolateDir, nextDirection);

			//目標角度を超えたら終了
			if (cross1.y * cross2.y < TARGET_ANGLE)
			{
				interPolateDir = nextDirection;
				rotateFlag = false;
			}

			//目標ベクトルに10度だけ近づけた角度
			direction = interPolateDir;
		}
	}

	EnemyRotateTime(deltaTime);
}

/// <summary>
/// エネミーの回転の時間
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Enemy::EnemyRotateTime(float deltaTime)
{
	rotateTime += deltaTime;

	RotateTime rotate[] =
	{
		{EnemyReaction::NORMAL, NOMAL_ROTATE_TIME},
		{EnemyReaction::PLAYER, PLAYER_ROTATE_TIME},
		{EnemyReaction::CAKE,	CAKE_ROTATE_TIME},
	};

	for (int i = 0; i < ROTATE_TIME_CATEGORY; i++)
	{
		//各オブジェクトによって回転の時間を変える
		if (enemyReaction == rotate[i].enemyReaction && rotateTime > rotate[i].time)
		{
			//スピードを元に戻す
			speed = changeSpeed;

			rotateTime = INITIAL_ROTATE_TIME;

			enemyState = EnemyState::ARRIVAL;
		}
	}
}

/// <summary>
/// エネミーの視野にプレイヤーが入った場合
/// </summary>
/// <param name="playerPosition">プレイヤーの座標</param>
void Enemy::VisualAnglePlayer(VECTOR playerPosition)
{
	//プレイヤーからエネミーの座標を引いた値を取得
	VECTOR sub = playerPosition - position;

	//プレイヤーとエネミーの距離を計算
	playerDirection = VSize(sub);

	//ベクトルの正規化
	sub = VNorm(sub);

	//内積計算
	float dot = VDot(sub, direction);

	float range = RANGE_DEGREE * (DX_PI_F / 180.0f);

	//エネミーの視野をcosにする
	float radian = cosf(range / 2.0f);

	//ベクトルとエネミーの長さの比較
	if (length > playerDirection)
	{
		//プレイヤーがエネミーの視野範囲内にいるならば
		if (radian <= dot)
		{
			enemyReaction = EnemyReaction::PLAYER;

			direction = sub;

			Reaction();
		}
	}
	else
	{
		playerSpotted = false;

		enemyReaction = EnemyReaction::NORMAL;
	}
}

/// <summary>
/// エネミーの視野にケーキが入った場合
/// </summary>
/// <param name="bulletPosition">バレットの座標</param>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Enemy::VisualAngleCake(VECTOR bulletPosition, float deltaTime)
{
	//バレットからエネミーの座標を引いた値を取得
	VECTOR sub = bulletPosition - position;

	//バレットとエネミーの距離を計算
	bulletDirection = VSize(sub);

	//ベクトルの正規化
	sub = VNorm(sub);

	//内積計算
	float dot = VDot(sub, direction);

	float range = RANGE_DEGREE * (DX_PI_F / 180.0f);

	//エネミーの視野をcosにする
	float radian = cosf(range / 2.0f);
	
	//ベクトルとエネミーの長さの比較
	if (length > bulletDirection)
	{
		//バレットがエネミーの視野範囲内にいるならば
		if (radian <= dot)
		{
			enemyReaction = EnemyReaction::CAKE;

			direction = sub;

			Reaction();

			CakeEatCount(deltaTime);
		}
	}
	else
	{
		//エネミーの視野範囲外ならスピードを元のスピードに戻す
		speed = changeSpeed;

		cakeFlag = false;

		cakeFindFlag = false;

		cakeEat = false;

		//カウントの初期化
		cakeCount = 0.0f;

		enemyReaction = EnemyReaction::NORMAL;
	}
}

/// <summary>
/// 秒数によってケーキの状態変化
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Enemy::CakeEatCount(float deltaTime)
{
	cakeCount += deltaTime;

	//ケーキを見つけてカウントが1.5秒経過したら
	if (cakeCount > 1.5f)
	{
		speed = changeSpeed;

		//ビックリマーク画像を非表示にする
		cakeFindFlag = false;
	}

	//ビックリマーク画像が非表示になったら
	if (/*230.0f > bulletDirection*/!cakeFindFlag)
	{
		speed = STOP_SPEED;

		cakeEat = true;
	}
}

/// <summary>
/// エネミーのオブジェクトごとの反応
/// </summary>
void Enemy::Reaction()
{
	switch (enemyReaction)
	{
	case EnemyReaction::NORMAL:
		break;

	case EnemyReaction::PLAYER:

		//プレイヤーを発見した
		playerSpotted = true;

		break;

	case EnemyReaction::CAKE:

		cakeFlag = true;

		//ケーキを見つけた
		cakeFindFlag = true;

		//エネミーの動きを止める
		speed = STOP_SPEED;
		
		break;
	}
}

/// <summary>
/// エネミーの状態の変化
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Enemy::StateUpdate(float deltaTime)
{
	switch (enemyState)
	{
	case EnemyState::CRAWL:

		//目的地にたどり着いたならば
		if (IsGoal(deltaTime))
		{
			targetPosition = *itr;

			//最終目的地に到着したら次の目的地に向かう
			if (itr == pointList.end())
			{
				itr = pointList.begin();
			}

			enemyState = EnemyState::ROTATION;
		}

		break;

	case EnemyState::ARRIVAL:
		SetTargetPosition();
		break;

	case EnemyState::ROTATION:
		
		//エネミーの動きを止める
		speed = STOP_SPEED;

		//エネミーを回転させる
		rotateFlag = true;
		
		EnemyRotate(deltaTime);

		break;
	}
}

/// <summary>
/// プレイヤーと衝突した
/// </summary>
void Enemy::HitPlayer()
{
	playerSpotted = true;
}

/// <summary>
/// リアクション画像の描画処理
/// </summary>
void Enemy::ReactionDraw()
{
	//プレイヤーを見つけたら
	if (playerSpotted)
	{
		//エネミーの動きを止める
		speed = STOP_SPEED;

		//ビックリマークの画像を描画
		DrawBillboard3D(VGet(position.x - 200.0f, 0.0f, position.z + 200.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//ケーキを見つけたならば
	if (cakeFindFlag)
	{
		//ビックリマーク画像を描画
		DrawBillboard3D(VGet(position.x - 200.0f, 0.0f, position.z + 200.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw()
{
	MV1DrawModel(modelHandle);

	MV1DrawModel(visualModelHandle);

	ReactionDraw();
}