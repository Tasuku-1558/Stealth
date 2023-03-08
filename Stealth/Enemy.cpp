#include "Enemy.h"
#include "ModelManager.h"
#include "Player.h"
#include "Bullet.h"

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="id"></param>
/// <param name="enemySpeed"></param>
Enemy::Enemy(vector<VECTOR>& id, float enemySpeed) : EnemyBase()
	, cakeCount(0.0f)
	, cakeFindFlag(false)
	, cakeEatFlag(false)
	, cakeHalfFlag(false)
	, IMAGE_FOLDER_PATH("Data/image/")
	, MARK_PATH("mark.png")
	, CAKE_PATH("ui8.png")
	, CAKE_HALF_PATH("cakeHalf.png")
	, enemyState(EnemyState::CRAWL)
	, futureDir()
	, rotate(false)
{
	Position(id);

	changeSpeed = enemySpeed;

	Initialize();
	Activate();
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

	//画像の読み込み
	markImage	 = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());

	cakeImage[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, CAKE_PATH).c_str());

	cakeImage[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, CAKE_HALF_PATH).c_str());
}

/// <summary>
/// 画像のパスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="imagePath"></param>
/// <returns></returns>
string Enemy::InputPath(string folderPath, string imagePath)
{
	return string(folderPath + imagePath);
}

/// <summary>
/// 活性化処理
/// </summary>
void Enemy::Activate()
{
	speed = changeSpeed;
	direction = ZERO_VECTOR;
	futureDir = ZERO_VECTOR;

	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// エネミー位置設定
/// </summary>
/// <param name="id"></param>
void Enemy::Position(vector<VECTOR>& id)
{
	pointList = id;					//マップから座標リストを受け取る

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

	for (int i = 0; i < CAKE_IMAGE_NUMBER; i++)
	{
		DeleteGraph(cakeImage[i]);
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Enemy::Update(float deltaTime, Player* player)
{
	StateUpdate(deltaTime);

	Move(deltaTime);

	VisualAnglePlayer(player);

	//当たり判定球の移動処理
	collisionSphere.Move(position);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime"></param>
void Enemy::Move(float deltaTime)
{
	if (enemyState == EnemyState::CRAWL || enemyState == EnemyState::ARRIVAL)
	{
		//ベクトルの正規化
		direction = VNorm(targetPosition - position);
	}
	
	if (enemyState == EnemyState::ROTATION)
	{
		//ベクトルの正規化
		direction = VNorm(direction);

		futureDir = VNorm(targetPosition - position);

		float a = powf(direction.x, 2.0f) + (0.0f) + powf(direction.z, 2.0f);

		float b = powf(futureDir.x, 2.0f) + (0.0f) + powf(futureDir.z, 2.0f);

		float cos = VDot(direction, futureDir) / (a * b);

		float sita = acosf(cos);

		sita = sita * 180.0f / DX_PI_F;

		if (rotate)
		{
			//回転が目標角度に十分近ければ回転をやめる
			if (IsNearAngle(direction, futureDir))
			{
				direction = futureDir;
				rotate = false;
			}
			else
			{
				//回転させる
				VECTOR d = RotateForAimVecYAxis(direction, futureDir, 4.0f);
			
				//回転が目標角度を超えていないか
				VECTOR cross1 = VCross(direction, futureDir);
				VECTOR cross2 = VCross(d, futureDir);

				//目標角度を超えたら終了
				if (cross1.y * cross2.y < 0.0f)
				{
					d = futureDir;
					direction = futureDir;
					rotate = false;
				}

				//目標ベクトルに10度だけ近づけた角度
				direction = d;
			}
		}
	}

	position += direction * speed * deltaTime;

	//エネミーの位置と向きをセット
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);

	//視野の位置と向きをセット
	MV1SetPosition(visualModelHandle, position);
	MV1SetRotationYUseDir(visualModelHandle, direction, 0.0f);
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
/// <param name="deltaTime"></param>
/// <returns></returns>
bool Enemy::IsGoal(float deltaTime)
{
	return VSize(targetPosition - position) < speed * deltaTime;
}

/// <summary>
/// エネミーの視野にプレイヤーが入った場合
/// </summary>
/// <param name="player"></param>
void Enemy::VisualAnglePlayer(Player* player)
{
	//プレイヤーからエネミーの座標を引いた値を取得
	VECTOR sub = player->GetPosition() - position;

	//プレイヤーとエネミーの距離を計算
	float playerDirection = VSize(sub);

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

			//視野範囲内ならば
			Reaction();
		}
	}
	else
	{
		playerSpotted = false;
	}
}

/// <summary>
/// エネミーの視野にケーキが入った場合
/// </summary>
/// <param name="bullet"></param>
/// <param name="deltaTime"></param>
void Enemy::VisualAngleCake(Bullet* bullet, float deltaTime)
{
	//バレットからエネミーの座標を引いた値を取得
	VECTOR sub = bullet->GetPosition() - position;

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

			//視野範囲内ならば
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

		cakeEatFlag = false;

		cakeHalfFlag = false;

		//カウントの初期化
		cakeCount = 0.0f;
	}
}

/// <summary>
/// 秒数によってケーキの状態変化
/// </summary>
/// <param name="deltaTime"></param>
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
	//ケーキの画像を表示する
	if (/*230.0f > bulletDirection*/!cakeFindFlag)
	{
		speed = 0.0f;
		cakeEatFlag = true;

		//カウントが4秒経過したら
		//半分になったケーキの画像を表示する
		if (cakeCount > 4.0f)
		{
			cakeEatFlag = false;

			cakeHalfFlag = true;
		}
	}
}

/// <summary>
/// エネミーのオブジェクトごとの反応
/// </summary>
void Enemy::Reaction()
{
	switch (enemyReaction)
	{
	case EnemyReaction::PLAYER:

		//プレイヤーを発見した
		playerSpotted = true;

		break;

	case EnemyReaction::CAKE:

		cakeFlag = true;

		//ケーキを見つけた
		cakeFindFlag = true;

		//エネミーの動きを止める
		speed = 0.0f;
		
		break;
	}
}

/// <summary>
/// エネミーの動き
/// </summary>
/// <param name="deltaTime"></param>
void Enemy::StateUpdate(float deltaTime)
{
	switch (enemyState)
	{
	case EnemyState::CRAWL:

		//目的地にたどり着いたならば
		if (IsGoal(deltaTime))
		{
			enemyState = EnemyState::ROTATION;
		}
			
		break;

	case EnemyState::ARRIVAL:
		SetTargetPosition();
		break;

	case EnemyState::ROTATION:

		//エネミーの動きを止める
		speed = 0.0f;
		rotate = true;
		
		if (CheckHitKey(KEY_INPUT_G))
		{
			speed = changeSpeed;
			rotate = false;
			enemyState = EnemyState::ARRIVAL;
		}

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
		speed = 0.0f;

		//ビックリマークの画像を描画
		DrawBillboard3D(VGet(position.x - 200.0f, 0.0f, position.z + 200.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//ケーキを見つけたならば
	if (cakeFindFlag)
	{
		//ビックリマーク画像を描画
		DrawBillboard3D(VGet(position.x - 200.0f, 400.0f, position.z + 200.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//ケーキがエネミーの視野角に入ったならば
	if (cakeEatFlag)
	{
		//ケーキの画像を描画
		DrawBillboard3D(VGet(position.x + 100.0f, 500.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, cakeImage[0], TRUE);
	}

	//ケーキがエネミーの視野角に入って4秒経過したら
	if (cakeHalfFlag)
	{
		//ケーキが半分の画像を描画
		DrawBillboard3D(VGet(position.x + 100.0f, 500.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, cakeImage[1], TRUE);
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