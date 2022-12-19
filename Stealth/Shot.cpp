#include "Shot.h"
#include <math.h>
#include "ModelManager.h"


const VECTOR Shot::SIZE  = { 2.0f, 2.0f, 2.0f };		//モデルの倍率
const float  Shot::SPEED = 200.0f;						//モデルのスピード
const VECTOR Shot::DIR	 = { 1.0f,0.0f,0.0f };

using namespace Math3d;

Shot::Shot()
{
}

Shot::~Shot()
{
	// 終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Shot::Initialize()
{
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::BOAL);
	MV1SetScale(modelHandle, SIZE);


	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [BOAL]\n");
	}
}

void Shot::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Shot::Activate()
{
	dir = DIR;
}

void Shot::Update(VECTOR position)
{
	OnShot(position);
}

//球が撃たれた時
void Shot::OnShot(VECTOR position)
{
	//position += dir * SPEED;

	MV1SetPosition(modelHandle, position);
}

void Shot::Draw()
{
	MV1DrawModel(modelHandle);
}