#include "Bullet.h"
#include "ModelManager.h"
#include "Player.h"


const VECTOR Bullet::SIZE  = { 2.0f, 2.0f, 2.0f };		//モデルの倍率
const float  Bullet::SPEED = 50.0f;						//モデルのスピード


using namespace Math3d;

Bullet::Bullet()
{
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
}

void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Bullet::Activate(/*Player* player*/)
{
	//position = player->GetPosition();
	//dir = player->GetDir();
	dir = VGet(-1.0f, 0.0f, 0.0f);
}

void Bullet::Update()
{
	OnShot();
	
}

/// <summary>
/// 球が撃たれた時
/// </summary>
void Bullet::OnShot()
{
	position += dir * SPEED;

	MV1SetPosition(modelHandle, position);
}

void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
}