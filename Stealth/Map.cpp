#include "Map.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR Map::SIZE	   = { 80.0f, 50.0f, 80.0f };						//モデルの倍率
const VECTOR Map::POSITION = { -2700.0f, -100.0f, -750.0f };				//モデルの位置
const VECTOR Map::ROTATE   = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };		//モデルの回転値

using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
Map::Map() : StageBase()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void Map::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE1));
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [STAGE1]\n");
	}

	MapList();
}

/// <summary>
/// 終了処理
/// </summary>
void Map::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// 敵の行動パターンリスト
/// </summary>
void Map::MapList()
{
	positionList.push_back(VGet(-3200.0f, 100.0f, 1400.0f));
	positionList.push_back(VGet(-3200.0f, 100.0f, -1300.0f));

	itr = positionList.begin();   //  イテレータを先頭に設定
}

void Map::MiniMap()
{
	/*pDotX = x + int(pGloX * exRate);
	pDotY = y + int(pGloY * exRate);*/

	DrawRotaGraph(x, y, exRate, 0, mapGraph, false);
	DrawBoxAA(mapFlameX, mapFlameY, mapFlameX + miniMapWidth, mapFlameY + miniMapHeight, GetColor(0, 0, 0), false, 3);
	DrawBoxAA(pDotX - int(SCREEN_WIDTH * exRate / 2), pDotY - int(SCREEN_HEIGHT * exRate / 2), pDotX + int(SCREEN_WIDTH * exRate / 2), pDotY + int(SCREEN_HEIGHT * exRate / 2), GetColor(255, 0, 0), false, 2);
	DrawCircle(pDotX, pDotY + 12, dotSize, GetColor(0, 0, 0), true);
}

/// <summary>
/// 描画処理
/// </summary>
void Map::Draw()
{
	MV1DrawModel(modelHandle);

	//MiniMap();
}