#include "Enemy.h"
#include "ModelManager.h"


const string Enemy::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string Enemy::SOUND_FOLDER_PATH = "data/sound/";		//soundフォルダまでのパス
const string Enemy::FIND_PATH		  = "find.png";			//見つかった画像のパス
const string Enemy::VIEW_RANGE_PATH	  = "view_range.png";
const string Enemy::MARK_PATH		  = "mark.png";			//ビックリマーク画像のパス
const string Enemy::DISCOVERY_SE_PATH = "discovery.mp3";	//プレイヤー発見SE音のパス


using namespace Math3d;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="map"></param>
Enemy::Enemy(Map* map) : EnemyBase()
{
	enemyState = EnemyState::CRAWL;
	Position(map);
}

Enemy::Enemy(SecondStageMap* secondStageMap) : EnemyBase()
{
	enemyState = EnemyState::CRAWL;
	FirstPosition(secondStageMap);
	Initialize();
	Activate();
	//SecondPosition(secondStageMap);
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Enemy::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[ENEMY_BODY]\n");
	}

	speed = SPEED;
	
	string failePath = IMAGE_FOLDER_PATH + FIND_PATH;
	findImage = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + VIEW_RANGE_PATH;
	viewRangeImage = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + MARK_PATH;
	markImage = LoadGraph(failePath.c_str());

	failePath = SOUND_FOLDER_PATH + DISCOVERY_SE_PATH;
	discoverySE = LoadSoundMem(failePath.c_str());
}

void Enemy::Activate()
{
	playerFindCount = 0;
}

/// <summary>
/// エネミー位置設定
/// </summary>
/// <param name="map"></param>
void Enemy::Position(Map* map)
{
	pointList = map->GetMap(0);		//マップから座標リストを受け取る

	itr = pointList.begin();		//イテレータを先頭に設定

	position = *itr++;				//イテレータから敵座標を設定

	enemyState = EnemyState::ARRIVAL;
}

void Enemy::FirstPosition(SecondStageMap* secondStageMap)
{
	pointList = secondStageMap->GetMap(0);		//マップから座標リストを受け取る

	itr = pointList.begin();		//イテレータを先頭に設定

	position = *itr++;				//イテレータから敵座標を設定

	enemyState = EnemyState::ARRIVAL;
}

void Enemy::SecondPosition(SecondStageMap* secondStageMap)
{
	pointList = secondStageMap->GetMap2(0);		//マップから座標リストを受け取る

	itr = pointList.begin();		//イテレータを先頭に設定

	position = *itr++;				//イテレータから敵座標を設定

	enemyState = EnemyState::ARRIVAL;
}

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	DeleteGraph(findImage);
	DeleteGraph(markImage);

	// サウンドリソースを削除
	InitSoundMem();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Enemy::Update(float deltaTime, Player* player)
{
	//エネミーの位置をセット
	MV1SetPosition(modelHandle, position);
	
	//ベクトルの正規化
	dir = VNorm(targetPosition - position);
	
	position += dir * speed * deltaTime;

	VisualAngle(player);

	VisualAngleBall(player);

	eUpdate(deltaTime);
	
	//z軸が逆を向いているのでdirを180度回転させる
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//モデルに回転をセット
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

/// <summary>
/// 移動処理
/// </summary>
void Enemy::SetTargetPosition()
{
	targetPosition = *itr++;

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
	return VSize(targetPosition - position) < SPEED * deltaTime;
}

/// <summary>
/// 視野角の計算
/// </summary>
/// <param name="player"></param>
void Enemy::VisualAngle(Player* player)
{
	//プレイヤーからエネミーの座標を引いた値を取得
	VECTOR sub = player->GetPosition() - position;

	//プレイヤーとエネミーの2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//ベクトルの正規化
	sub = VNorm(sub);

	//内積計算
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//エネミーの視野をcosにする
	float radian = cosf(range / 2.0f);

	//発見していない
	discovery = false;
	
	//ベクトルとエネミーの長さの比較
	if (length > direction)
	{
		//プレイヤーがエネミーの視野範囲内にいるか比較
		if (radian <= dot)
		{
			object = PLAYER;
			
			//視野範囲内ならば
			Reaction(object);
		}
	}
}

void Enemy::VisualAngleBall(Player* player)
{
	//プレイヤーからエネミーの座標を引いた値を取得
	VECTOR sub = player->GetBulletPos() - position;

	//プレイヤーとエネミーの2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//ベクトルの正規化
	sub = VNorm(sub);

	//内積計算
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//エネミーの視野をcosにする
	float radian = cosf(range / 2.0f);

	ballFlag = false;

	//ベクトルとエネミーの長さの比較
	if (length > direction)
	{
		//プレイヤーがエネミーの視野範囲内にいるか比較
		if (radian <= dot)
		{
			object = BALL;

			//視野範囲内ならば
			Reaction(object);

			
		}
	}
}

/// <summary>
/// エネミーのオブジェクトごとの反応
/// </summary>
/// <param name="object"></param>
void Enemy::Reaction(Object object)
{
	switch (object)
	{
	case ObjectBase::PLAYER:
		//printfDx("PLAYER");
		discovery = true;

		// 発見SEを再生
		PlaySoundMem(discoverySE, DX_PLAYTYPE_BACK);

		//ビックリマークの画像を描画
		DrawBillboard3D(VGet(position.x - 300, 0.0f, position.z - 100), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);

		DrawGraph(300, 100, findImage, TRUE);		//敵に見つかったというUI画像を描画
		playerFindCount++;
		break;

	case ObjectBase::BALL:
		//printfDx("BALL");
	
		ballFlag = true;
		if (ballFlag)
		{
			speed = 0.0f;
			count++;
			if (count > 200)
			{
				speed = SPEED;
				ballFlag = false;
				
			}
			
		}
		else
		{
			speed = SPEED;
		}
		
		break;

	case ObjectBase::WALL:
		printfDx("WALL");
		break;
	}
}

/// <summary>
/// エネミーの状態
/// </summary>
/// <param name="deltaTime"></param>
void Enemy::eUpdate(float deltaTime)
{
	switch (enemyState)
	{
	case EnemyState::CRAWL:

		if (IsGoal(deltaTime))
		{
			enemyState = EnemyState::ARRIVAL;
		}
		break;

	case EnemyState::ARRIVAL:
		SetTargetPosition();
		break;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw()
{
	MV1DrawModel(modelHandle);
	//DrawBillboard3D(VGet(position.x - 10, 30.0f, position.z + 200), 0.5f, 0.5f, 300.0f, 0.0f, viewRangeImage, TRUE);
}