#include "Enemy.h"
#include "ModelManager.h"
#include "Map.h"
#include "Player.h"


const string Enemy::IMAGE_FOLDER_PATH = "data/image/";     //imageフォルダまでのパス
const string Enemy::FIND_PATH = "a.png";		//カーソル画像のパス


using namespace Math3d;
using namespace std;

/// <summary>
/// コンストラク
/// </summary>
/// <param name="map"></param>
Enemy::Enemy(Map* map) : EnemyBase()
	, object()
	, targetPosition()
	, length(400.0f)
	, discovery(false)
	, playerFindCount(0)
	, findImage(0)
{
	enemyState = EnemyState::CRAWL;
	Position(map);
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
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_BODY));

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[ENEMY_BODY]\n");
	}

	string failePath = IMAGE_FOLDER_PATH + FIND_PATH;
	findImage = LoadGraph(failePath.c_str());
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

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	DeleteGraph(findImage);
}

void Enemy::Activate()
{
}

void Enemy::Update(float deltaTime, Player* player)
{
	//エネミーの位置をセット
	MV1SetPosition(modelHandle, position);
	
	//ベクトルの正規化
	dir = VNorm(targetPosition - position);
	
	//position += dir * SPEED * deltaTime;

	VisualAngle(player);

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
	//プレイヤーとエネミーの距離を取得
	VECTOR sub = player->GetPosition() - position;

	//距離をfloatに置き換え
	float direction = VSize(sub);

	//エネミーの前方とプレイヤーの位置の角度
	float radian = VDot(player->GetPosition(), dir);

	//float a = RANGE_DEGREE * (float)(DX_PI / 180.0f);
	//float b = radian * (float)(DX_PI / 180.0f);


	float range_Cos = cosf(RANGE_DEGREE * (float)(DX_PI / 180.0f));
	float radian_Cos = cosf(radian * (float)(DX_PI / 180.0f));

	discovery = false;
	

	// 見つかっているかどうか
	if (length > direction)
	{
		//printfDx("索敵範囲内");

		//プレイヤーを発見
		if (radian_Cos <= range_Cos)
		{
			//printfDx("発見");
			
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
		printfDx("PLAYER");
		discovery = true;

		DrawGraph(0, -50, findImage, TRUE);
		playerFindCount++;
		break;

	case ObjectBase::BALL:
		printfDx("BALL");
		break;

	case ObjectBase::WALL:
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
}