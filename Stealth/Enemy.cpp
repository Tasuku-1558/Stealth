#include "Enemy.h"
#include "ModelManager.h"


const string Enemy::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string Enemy::FIND_PATH		  = "find.png";			//見つかった画像のパス


using namespace Math3d;
using namespace std;

/// <summary>
/// コンストラクタ
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
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

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

void Enemy::Update(float deltaTime, Player* player)
{
	//エネミーの位置をセット
	MV1SetPosition(modelHandle, position);
	
	//ベクトルの正規化
	dir = VNorm(targetPosition - position);
	
	position += dir * SPEED * deltaTime;

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
		printfDx("PLAYER");
		discovery = true;

		DrawGraph(200, 0, findImage, TRUE);		//敵に見つかったというUI画像を描画
		playerFindCount++;
		break;

	case ObjectBase::BALL:
		printfDx("BALL");
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
}