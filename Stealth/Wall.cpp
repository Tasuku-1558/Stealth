#include "Wall.h"
#include "ModelManager.h"


const VECTOR Wall::SIZE		= { 2.0f, 2.0f, 2.0f };		//モデルの倍率
const VECTOR Wall::POSITION = { -2500.0f,30.0f,0.0f };	//モデルの位置


/// <summary>
/// コンストラク
/// </summary>
/// <param name="WALL"></param>
Wall::Wall(Object WALL)
{
	//処理なし
}

Wall::~Wall()
{
	// 終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Wall::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::WALL));
	MV1SetScale(modelHandle, SIZE);

	position = POSITION;
	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [WALL]\n");
	}
}

void Wall::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Wall::Draw()
{
	MV1DrawModel(modelHandle);
}