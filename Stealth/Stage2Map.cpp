#include "Stage2Map.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR Stage2Map::SIZE	 = { 80.0f, 50.0f, 80.0f };					//モデルの倍率
const VECTOR Stage2Map::POSITION = { -200.0f, 50.0f, 1350.0f };				//モデルの位置

using namespace std;

Stage2Map::Stage2Map() : ObjectBase()
{
	//処理なし
}

Stage2Map::~Stage2Map()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Stage2Map::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE2));
	MV1SetScale(modelHandle, SIZE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [STAGE1]\n");
	}

	MapList();
}

void Stage2Map::MapList()
{
	positionList.push_back(VGet(-3200.0f, 100.0f, 1400.0f));
	positionList.push_back(VGet(-3200.0f, 100.0f, -1300.0f));

	itr = positionList.begin();   //  イテレータを先頭に設定
}

void Stage2Map::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Stage2Map::Draw()
{
	MV1DrawModel(modelHandle);
}