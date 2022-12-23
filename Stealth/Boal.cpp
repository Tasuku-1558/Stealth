#include "Boal.h"
#include "ModelManager.h"
#include "HitChecker.h"


const VECTOR Boal::SIZE		= { 2.0f, 2.0f, 2.0f };		//モデルの倍率
const VECTOR Boal::POSITION = { -1500.0f,30.0f,0.0f };	//モデルの位置

Boal::Boal() : ObjectBase()
	, alive(true)
{
	//処理なし
}

Boal::~Boal()
{
	// 終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Boal::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BOAL));
	MV1SetScale(modelHandle, SIZE);


	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [BOAL]\n");
	}
}

void Boal::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Boal::Activate()
{
	position = POSITION;
}

void Boal::Update()
{
	MV1SetPosition(modelHandle, position);
}

void Boal::Draw()
{
	MV1DrawModel(modelHandle);
}

/// <summary>
/// 生きてるか死んでいるか
/// </summary>
/// <param name="hitChecker"></param>
void Boal::IsAlive(HitChecker* hitChecker)
{
	if (hitChecker->Hit())
	{
		alive = false;
	}
	else
	{
		alive = true;
	}
}