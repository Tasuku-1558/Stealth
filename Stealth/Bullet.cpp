#include "Bullet.h"
#include "ModelManager.h"


const VECTOR Bullet::SIZE			   = { 2.0f, 2.0f, 2.0f };	//モデルの倍率
const VECTOR Bullet::POSITION		   = { 0.0f, 30.0f, 0.0f }; //モデルの位置
const string Bullet::IMAGE_FOLDER_PATH = "data/image/";			//imageフォルダまでのパス
const string Bullet::CURSOR_PATH	   = "pointer.png";			//カーソル画像のパス
const float  Bullet::SCALE			   = 0.4f;					//カーソル画像の大きさ

using namespace Math3d;

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
	: cursorImage(0)
	, mouseX(0)
	, mouseZ(0)
	, worldMouseX(0.0f)
	, worldMouseZ(0.0f)
	, alive(false)
{
	//処理なし
}

Bullet::~Bullet()
{
	// 終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Bullet::Initialize()
{
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::BALL);
	MV1SetScale(modelHandle, SIZE);

	// マウスカーソルを表示しない
	SetMouseDispFlag(FALSE);

	position = POSITION;

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [BULLET]\n");
	}

	string failePath = IMAGE_FOLDER_PATH + CURSOR_PATH;
	cursorImage = LoadGraph(failePath.c_str());
}

void Bullet::Activate()
{
	position = POSITION;
}

void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	DeleteGraph(cursorImage);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="ball"></param>
void Bullet::Update(float deltaTime, Ball* ball)
{
	if (!ball->GetAlive())
	{
		OnShot(deltaTime);
	}
}

/// <summary>
/// マウスカーソルの移動
/// </summary>
/// <param name="ball"></param>
/// <param name="pos"></param>
void Bullet::MouseMove(Ball* ball, VECTOR playerPos)
{
	GetMousePoint(&mouseX, &mouseZ);                //マウスの座標取得
	mouseX -= 960;
	mouseZ -= 540;

	//ボールが死んだら
	if (!ball->GetAlive())
	{
		//マウスのXZ座標のワールド座標を計算
		worldMouseX = (float)mouseX * (3000.0f / 1920.0f) * 1.6f + playerPos.z;
		worldMouseZ = (float)mouseZ * (1900.0f / 1080.0f) * 1.5f + playerPos.x;
	}
}

/// <summary>
/// バレットを非アクティブ化
/// </summary>
void Bullet::BulletDead()
{
	alive = false;
	position = POSITION;
}

/// <summary>
/// バレットをアクティブ化
/// </summary>
void Bullet::BulletAlive()
{
	alive = true;
}

/// <summary>
/// 球が撃たれた時
/// </summary>
/// <param name="deltaTime"></param>
void Bullet::OnShot(float deltaTime)
{
	position = VGet(worldMouseZ, 30.0f, worldMouseX);

	MV1SetPosition(modelHandle, position);
}

void Bullet::Draw()
{
	if (alive)
	{
		MV1DrawModel(modelHandle);
	}

	DrawRotaGraph(mouseX + 960, mouseZ + 540, SCALE, 0, cursorImage, TRUE);
}