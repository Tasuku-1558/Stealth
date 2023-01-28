#include "Enemy.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Bullet.h"

const string Enemy::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string Enemy::SOUND_FOLDER_PATH = "data/sound/";		//soundフォルダまでのパス
const string Enemy::FIND_PATH		  = "find.png";			//見つかった画像のパス
const string Enemy::MARK_PATH		  = "mark.png";			//ビックリマーク画像のパス
const string Enemy::SPOTTED_SE_PATH	  = "spotted.mp3";		//プレイヤー発見SE音のパス


using namespace Math3d;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="id"></param>
Enemy::Enemy(std::vector<VECTOR>& id) : EnemyBase()
{
	enemyState = EnemyState::CRAWL;
	Position(id);

	Initialize();
	Activate();
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

/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//読み込み失敗でエラー
	if (modelHandle < 0 || visualModelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[ENEMY]\n");
	}

	speed = SPEED;

	dir = ZERO_VECTOR;

	string failePath = IMAGE_FOLDER_PATH + FIND_PATH;
	findImage = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + MARK_PATH;
	markImage = LoadGraph(failePath.c_str());

	failePath = SOUND_FOLDER_PATH + SPOTTED_SE_PATH;
	spottedSE = LoadSoundMem(failePath.c_str());
}

/// <summary>
/// 活性化処理
/// </summary>
void Enemy::Activate()
{
	playerFindCount = 0;
	dir = ZERO_VECTOR;
	speed = SPEED;
}

/// <summary>
/// エネミー位置設定
/// </summary>
/// <param name="num"></param>
void Enemy::Position(std::vector<VECTOR>& id)
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
	DeleteGraph(findImage);
	DeleteGraph(markImage);

	//サウンドリソースを削除
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

	//エネミーの視野モデルをセット
	MV1SetPosition(visualModelHandle, position);
	
	//ベクトルの正規化
	dir = VNorm(targetPosition - position);
	
	position += dir * speed * deltaTime;

	VisualAngle(player);
	
	eUpdate(deltaTime);
	
	//z軸が逆を向いているのでdirを180度回転させる
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//モデルに回転をセット
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	MV1SetRotationZYAxis(visualModelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

/// <summary>
/// 目的地まで移動処理
/// </summary>
void Enemy::SetTargetPosition()
{
	targetPosition = *itr++;

	//最終目的地に到着したら次の目的地を初期位置にする
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
/// エネミーの視野にプレイヤーが入った場合
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

	//ベクトルとエネミーの長さの比較
	if (length > direction)
	{
		//プレイヤーがエネミーの視野範囲内にいるか比較
		if (radian <= dot)
		{
			object = Object::PLAYER;

			//プレイヤーを発見した
			playerSpotted = true;

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
/// エネミーの視野にボールが入った場合
/// </summary>
/// <param name="bullet"></param>
void Enemy::VisualAngleBall(Bullet* bullet)
{
	//バレットからエネミーの座標を引いた値を取得
	VECTOR sub = bullet->GetPosition() - position;

	//バレットとエネミーの2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//ベクトルの正規化
	sub = VNorm(sub);

	//内積計算
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//エネミーの視野をcosにする
	float radian = cosf(range / 2.0f);
	
	//ベクトルとエネミーの長さの比較
	if (length > direction)
	{
		//バレットがエネミーの視野範囲内にいるか比較
		if (radian <= dot)
		{
			object = Object::BALL;

			//ボールを見つけた
			ballFlag = true;


			//視野範囲内ならば
			Reaction();
		}
	}
	else
	{
		//エネミーの視野範囲外ならスピードを元のスピードに戻す
		speed = SPEED;

		ballFlag = false;
	}
}

/// <summary>
/// エネミーの視野に壁が入った場合
/// </summary>
/// <param name="wallPos"></param>
void Enemy::VisualAngleWall(VECTOR wallPos)
{
	//壁からエネミーの座標を引いた値を取得
	VECTOR sub = wallPos - position;

	//壁とエネミーの2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//ベクトルの正規化
	sub = VNorm(sub);

	//内積計算
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//エネミーの視野をcosにする
	float radian = cosf(range / 2.0f);

	//ベクトルとエネミーの長さの比較
	if (length > direction)
	{
		//壁がエネミーの視野範囲内にいるか比較
		if (radian <= dot)
		{
			object = Object::WALL;

			//視野範囲内ならば
			Reaction();
		}
	}
}

/// <summary>
/// エネミーのオブジェクトごとの反応
/// </summary>
void Enemy::Reaction()
{
	switch (object)
	{
	case Object::PLAYER:
		//printfDx("PLAYER");
		
		//ビックリマークの画像を描画
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);

		//敵に見つかったというUI画像を描画
		DrawGraph(50, 50, findImage, TRUE);

		// 発見SEを再生
		PlaySoundMem(spottedSE, DX_PLAYTYPE_BACK);
	
		
		playerFindCount++;
		break;

	case Object::BALL:
		//printfDx("BALL");
		
		speed = 0.0f;
		
		break;

	case Object::WALL:
		//printfDx("WALL");

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

	MV1DrawModel(visualModelHandle);
}