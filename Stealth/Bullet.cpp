#include "Bullet.h"
#include "ModelManager.h"
#include "Boal.h"


const VECTOR Bullet::SIZE  = { 2.0f, 2.0f, 2.0f };			//モデルの倍率
const float  Bullet::SPEED = 800.0f;						//モデルのスピード
const string Bullet::IMAGE_FOLDER_PATH = "data/image/";     //imageフォルダまでのパス
const string Bullet::CURSOR_PATH	   = "pointer.png";		//カーソル画像のパス


using namespace Math3d;

Bullet::Bullet(Object BOAL)
	: cursorImage(0)
	, mouseX(-50)
	, mouseY(0)
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
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::BOAL);
	MV1SetScale(modelHandle, SIZE);


	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [BOAL]\n");
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
	
	position = VGet(0.0f, 0.0f, 0.0f);
}

void Bullet::Update(float deltaTime, Boal* boal)
{
	if (!boal->GetAlive())
	{
		OnShot(deltaTime);
		//MouseMove(boal);
	}
	
}

/// <summary>
/// マウスカーソルの移動
/// </summary>
/// <param name="boal"></param>
void Bullet::MouseMove(Boal* boal)
{
	if (!boal->GetAlive())
	{
		GetMousePoint(&mouseX, &mouseY);                //マウスの座標取得
	}
}

/// <summary>
/// 球が撃たれた時
/// </summary>
/// <param name="deltaTime"></param>
void Bullet::OnShot(float deltaTime)
{
	
	position += VGet(mouseY-2700, 0.0f, mouseX-500);

	MV1SetPosition(modelHandle, position);
}

void Bullet::Draw()
{
	MV1DrawModel(modelHandle);

	DrawRotaGraph(mouseX, mouseY, 0.04f, 0, cursorImage, TRUE);
}