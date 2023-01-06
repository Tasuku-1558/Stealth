#include "Bullet.h"
#include "ModelManager.h"


const VECTOR Bullet::SIZE  = { 2.0f, 2.0f, 2.0f };			//モデルの倍率
const float  Bullet::SPEED = 800.0f;						//モデルのスピード
const string Bullet::IMAGE_FOLDER_PATH = "data/image/";     //imageフォルダまでのパス
const string Bullet::CURSOR_PATH	   = "pointer.png";		//カーソル画像のパス


using namespace Math3d;

Bullet::Bullet(Object BALL)
	: cursorImage(0)
	, mouseX(0)
	, mouseY(0)
	, worldMouseX(0.0f)
	, worldMouseY(0.0f)
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

	position = VGet(0.0f, 30.0f, 0.0f);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [BALL]\n");
	}

	string failePath = IMAGE_FOLDER_PATH + CURSOR_PATH;
	cursorImage = LoadGraph(failePath.c_str());
}

void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	DeleteGraph(cursorImage);
}

void Bullet::Activate()
{
}

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
void Bullet::MouseMove(Ball* ball, VECTOR pos)
{
	GetMousePoint(&mouseX, &mouseY);                //マウスの座標取得
	mouseX -= 960;
	mouseY -= 540;

	if (!ball->GetAlive())
	{
		worldMouseX = (float)mouseX * (3000.0f / 1920.0f) * 2.0f + pos.z;
		worldMouseY = (float)mouseY * (1900.0f / 1080.0f) * 1.8f + pos.x;
	}
}

/// <summary>
/// バレットを非アクティブ化
/// </summary>
void Bullet::SetDead()
{
	alive = false;
}

/// <summary>
/// バレットをアクティブ化
/// </summary>
void Bullet::SetAlive()
{
	alive = true;
}

/// <summary>
/// 球が撃たれた時
/// </summary>
/// <param name="deltaTime"></param>
void Bullet::OnShot(float deltaTime)
{
	position = VGet(worldMouseY, 30.0f, worldMouseX);

	MV1SetPosition(modelHandle, position);
}

void Bullet::Draw()
{
	if (alive)
	{
		MV1DrawModel(modelHandle);
	}

	DrawRotaGraph(mouseX + 960, mouseY + 540, 0.04f, 0, cursorImage, TRUE);
}