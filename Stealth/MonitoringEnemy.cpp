#include "MonitoringEnemy.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Bullet.h"

const string MonitoringEnemy::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string MonitoringEnemy::PLAYER_FIND_PATH	= "playerFind.png";		//プレイヤーを見つけた画像のパス
const string MonitoringEnemy::MARK_PATH			= "mark.png";			//ビックリマーク画像のパス

using namespace Math3d;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
MonitoringEnemy::MonitoringEnemy(const VECTOR& pos, VECTOR changeDir) : EnemyBase()	
	, dirCount(0.0f)
	, anotherDir()
{
	position = pos;
	anotherDir = changeDir;

	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
MonitoringEnemy::~MonitoringEnemy()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void MonitoringEnemy::Initialize()
{
	//モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));
	MV1SetDifColorScale(modelHandle, GetColorF(0.0f, 0.5f, 2.0f, 1.0f));

	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//読み込み失敗でエラー
	if (modelHandle < 0 || visualModelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗\n");
	}

	//画像の読み込み
	playerFindImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());

	markImage		= LoadGraph(InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());
}

/// <summary>
/// 画像のパスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="imagePath"></param>
/// <returns></returns>
std::string MonitoringEnemy::InputPath(string folderPath, string imagePath)
{
	return std::string(folderPath + imagePath);
}

/// <summary>
/// 活性化処理
/// </summary>
void MonitoringEnemy::Activate()
{
	dir = ZERO_VECTOR;
	playerSpotted = false;
	cakeFlag = false;
}

/// <summary>
/// 終了処理
/// </summary>
void MonitoringEnemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(visualModelHandle);

	DeleteGraph(playerFindImage);
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
void MonitoringEnemy::Update(float deltaTime, Player* player)
{
	//ベクトルの正規化
	dir = VNorm(dir);

	DirMove(deltaTime);

	position += dir * deltaTime;

	//エネミーの位置をセット
	MV1SetPosition(modelHandle, position);

	//エネミーの視野モデルをセット
	MV1SetPosition(visualModelHandle, position);

	VisualAnglePlayer(player);

	//z軸が逆を向いているのでdirを180度回転させる
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//モデルに回転をセット
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	MV1SetRotationZYAxis(visualModelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

/// <summary>
/// エネミーの向きの処理
/// </summary>
/// <param name="deltaTime"></param>
void MonitoringEnemy::DirMove(float deltaTime)
{
	dirCount += deltaTime;

	//2秒経過したらエネミーの向きを変更する
	if (dirCount > 2.0f)
	{
		dir = anotherDir;
	}
	else
	{
		dir = { 0.0f,0.0f,-1.0f };
	}

	//4秒経過したらカウントを0にする
	if (dirCount > 4.0f)
	{
		dirCount = 0.0f;
	}
}

/// <summary>
/// エネミーの視野にプレイヤーが入った場合
/// </summary>
/// <param name="player"></param>
void MonitoringEnemy::VisualAnglePlayer(Player* player)
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
/// エネミーのプレイヤーの反応
/// </summary>
void MonitoringEnemy::Reaction()
{
	switch (object)
	{
	case Object::PLAYER:

		//プレイヤーを発見した
		playerSpotted = true;

		break;
	}
}

/// <summary>
/// リアクション画像の描画処理
/// </summary>
void MonitoringEnemy::ReactionDraw()
{
	//エネミーに見つかったら
	if (playerSpotted)
	{
		//ビックリマークの画像を描画
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);

		//敵に見つかったというUI画像を描画
		DrawGraph(50, -100, playerFindImage, TRUE);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void MonitoringEnemy::Draw()
{
	ReactionDraw();

	MV1DrawModel(modelHandle);

	MV1DrawModel(visualModelHandle);
}