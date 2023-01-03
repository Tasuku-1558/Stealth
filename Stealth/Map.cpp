#include "Map.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR Map::SIZE	   = { 80.0f, 50.0f, 80.0f };		//モデルの倍率
const VECTOR Map::POSITION = { -2700.0f, 0.0f, -750.0f };	//モデルの位置

using namespace Math3d;
using namespace std;

Map::Map() : ObjectBase()
	, collisionModel(0)
{
	//処理なし
}

Map::~Map()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Map::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE1));
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [STAGE1]\n");
	}


	/*collisionModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE1));

	MV1SetScale(collisionModel, SIZE);
	MV1SetRotationXYZ(collisionModel, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	position = POSITION;

	MV1SetPosition(collisionModel, position + VGet(-45, 0, -35));

	MV1SetupCollInfo(collisionModel);*/

	MapList();
}

void Map::MapList()
{
	positionList.push_back(VGet(-3200.0f, 100.0f, 1400.0f));
	positionList.push_back(VGet(-3200.0f, 100.0f, -1300.0f));

	itr = positionList.begin();   //  イテレータを先頭に設定
}

void Map::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Map::Activate()
{
}

void Map::Draw()
{
	MV1DrawModel(modelHandle);

	// コリジョンモデルが存在する場合は半透明描画
	/*if (collisionModel != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		MV1DrawModel(collisionModel);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}*/
}