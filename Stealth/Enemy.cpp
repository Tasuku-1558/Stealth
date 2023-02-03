#include "Enemy.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Bullet.h"

const string Enemy::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string Enemy::SOUND_FOLDER_PATH = "data/sound/";		//soundフォルダまでのパス
const string Enemy::PLAYER_FIND_PATH  = "playerFind.png";	//プレイヤーを見つけた画像のパス
const string Enemy::MARK_PATH		  = "mark.png";			//ビックリマーク画像のパス
const string Enemy::CAKE_PATH		  = "ui9.png";			//ケーキ画像のパス
const string Enemy::CAKE_HALF_PATH	  = "cakeHalf.png";		//ケーキが半分画像のパス
const string Enemy::SPOTTED_SE_PATH	  = "spotted.mp3";		//プレイヤー発見SE音のパス


using namespace Math3d;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="id"></param>
Enemy::Enemy(std::vector<VECTOR>& id) : EnemyBase()
	, cakeCount(0.0f)
	, cakeFindFlag(false)
	, cakeEatFlag(false)
	, cakeHalfFlag(false)
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
	//モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//読み込み失敗でエラー
	if (modelHandle < 0 || visualModelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗\n");
	}

	dir = ZERO_VECTOR;

	//画像読み込み
	playerFindImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());

	markImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());

	cakeImage[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, CAKE_PATH).c_str());

	cakeImage[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, CAKE_HALF_PATH).c_str());

	spottedSE = LoadSoundMem(InputPath(SOUND_FOLDER_PATH, SPOTTED_SE_PATH).c_str());
}

/// <summary>
/// 画像、SEのパスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
std::string Enemy::InputPath(string folderPath, string path)
{
	return std::string(folderPath + path);
}

/// <summary>
/// 活性化処理
/// </summary>
void Enemy::Activate()
{
	dir = ZERO_VECTOR;
	speed = SPEED;
	playerSpotted = false;
	cakeFlag = false;
	cakeFindFlag = false;
	cakeEatFlag = false;
	cakeHalfFlag = false;
	cakeCount = 0.0f;
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

	DeleteGraph(playerFindImage);
	DeleteGraph(markImage);

	for (int i = 0; i < CAKE_IMAGE_NUMBER; i++)
	{
		DeleteGraph(cakeImage[i]);
	}

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

	VisualAnglePlayer(player);
	
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
		//プレイヤーがエネミーの視野範囲内にいるならば
		if (radian <= dot)
		{
			object = Object::PLAYER;

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

	//バレットとエネミーの2点間の距離を計算
	bulletDirection = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//ベクトルの正規化
	sub = VNorm(sub);

	//内積計算
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//エネミーの視野をcosにする
	float radian = cosf(range / 2.0f);
	
	//ベクトルとエネミーの長さの比較
	if (length > bulletDirection)
	{
		//バレットがエネミーの視野範囲内にいるならば
		if (radian <= dot)
		{
			object = Object::CAKE;

			//視野範囲内ならば
			Reaction();

			CakeEatCount(deltaTime);
		}
	}
	else
	{
		//エネミーの視野範囲外ならスピードを元のスピードに戻す
		speed = SPEED;

		cakeFlag = false;

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
		speed = SPEED;

		//ビックリマーク画像を非表示にする
		cakeFindFlag = false;
	}

	//ケーキを見つけてエネミーがこの位置まで移動したら
	//ケーキの画像を表示する
	if (270.0f > bulletDirection)
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
		//壁がエネミーの視野範囲内にいるならば
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

		//プレイヤーを発見した
		playerSpotted = true;

		break;

	case Object::CAKE:

		cakeFlag = true;

		//ケーキを見つけた
		cakeFindFlag = true;

		//エネミーの動きを止める
		speed = 0.0f;
		
		break;

	case Object::WALL:
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
/// リアクション画像の描画処理
/// </summary>
void Enemy::ReactionDraw()
{
	//エネミーに見つかったら
	if (playerSpotted)
	{
		//エネミーの動きを止める
		speed = 0.0f;

		//ビックリマークの画像を描画
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);

		//敵に見つかったというUI画像を描画
		DrawGraph(50, -100, playerFindImage, TRUE);

		// 発見SEを再生
		//PlaySoundMem(spottedSE, DX_PLAYTYPE_BACK);
	}

	//ケーキを見つけたならば
	if (cakeFindFlag)
	{
		//ビックリマーク画像を描画
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//ケーキにエネミーが近づいたならば
	if (cakeEatFlag)
	{
		//ケーキの画像を描画
		DrawBillboard3D(VGet(position.x + 100.0f, 800.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, cakeImage[0], TRUE);
	}

	//ケーキがエネミーに近づいて4秒経過したら
	if (cakeHalfFlag)
	{
		//ケーキが半分の画像を描画
		DrawBillboard3D(VGet(position.x + 100.0f, 800.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, cakeImage[1], TRUE);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw()
{
	ReactionDraw();

	MV1DrawModel(modelHandle);

	MV1DrawModel(visualModelHandle);
}