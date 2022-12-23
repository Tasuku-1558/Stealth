#include "Bullet.h"
#include "ModelManager.h"
#include "Boal.h"


const VECTOR Bullet::SIZE  = { 2.0f, 2.0f, 2.0f };		//モデルの倍率
const float  Bullet::SPEED = 800.0f;						//モデルのスピード


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

void Bullet::Activate(VECTOR inPosition, VECTOR inDir)
{
	position = inPosition;
	dir = inDir;
	
}

void Bullet::Update(float deltaTime, Boal* boal)
{
	if (!boal->GetAlive())
	{
		OnShot(deltaTime);
	}
	else
	{
		return;
	}
	
}

/// <summary>
/// 球が撃たれた時
/// </summary>
void Bullet::OnShot(float deltaTime)
{
	position += dir * deltaTime * SPEED;

	MV1SetPosition(modelHandle, position);
	
}

void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
}