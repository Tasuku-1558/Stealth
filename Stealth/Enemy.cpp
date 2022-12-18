#include "Enemy.h"
#include "ModelManager.h"
#include "Map.h"
#include "Common.h"


using namespace Math3d;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy() : EnemyBase()
	, targetPosition()
{
	enemyState = EnemyState::Crawl;
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

void Enemy::Initialize(Map* map)
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_BODY));

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[ENEMY_BODY]\n");
	}

	Position(map);
}

/// <summary>
/// エネミー位置設定
/// </summary>
void Enemy::Position(Map* map)
{
	pointList = map->GetMap(0);		//マップから座標リストを受け取る

	itr = pointList.begin();		//イテレータを先頭に設定

	position = *itr++;				//イテレータから敵座標を設定

	enemyState = EnemyState::Arrival;
}

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Activate()
{
}

void Enemy::Update(float deltaTime)
{
	//エネミーの位置をセット
	MV1SetPosition(modelHandle, position);

	//ベクトルの正規化
	dir = VNorm(targetPosition - position);

	position += dir * SPEED * deltaTime;

	eUpdate(deltaTime);

	//z軸が逆を向いているのでdirを180度回転させる
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//モデルに回転をセット dirを向く
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

	enemyState = EnemyState::Crawl;
}

//目的地に到達したならば
bool Enemy::IsGoal(float deltaTime)
{
	return VSize(targetPosition - position) < SPEED * deltaTime;
}

//エネミーの状態
void Enemy::eUpdate(float deltaTime)
{
	switch (enemyState)
	{
	case EnemyState::Crawl:

		if (IsGoal(deltaTime))
		{
			enemyState = EnemyState::Arrival;
		}
		break;

	case EnemyState::Arrival:
		SetTargetPosition();
		break;

	case EnemyState::Discovery:
		break;
	}
}

void Enemy::Draw()
{
	MV1DrawModel(modelHandle);
}