#include "ThirdStageMap.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR ThirdStageMap::SIZE	 = { 60.0f, 60.0f, 60.0f };						//モデルの倍率
const VECTOR ThirdStageMap::POSITION = { -1800.0f, -100.0f, 1900.0f };				//モデルの位置
const VECTOR ThirdStageMap::ROTATE	 = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };	//モデルの回転値


using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
ThirdStageMap::ThirdStageMap() : StageBase()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ThirdStageMap::~ThirdStageMap()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void ThirdStageMap::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE3));
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [STAGE3]\n");
	}

	MapList();
	MapList2();
}

/// <summary>
/// 終了処理
/// </summary>
void ThirdStageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 敵の行動パターンリスト(上下に移動する敵)
/// </summary>
void ThirdStageMap::MapList()
{
	positionList.push_back({ -1700.0f, 0.0f, 1000.0f });
	positionList.push_back({ -1100.0f, 0.0f, 1000.0f });

	itr = positionList.begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト2(ゴールの位置を塞ぐ敵)
/// </summary>
void ThirdStageMap::MapList2()
{
	positionList2.push_back({ -2000.0f, 0.0f,  3000.0f });
	positionList2.push_back({ -2000.0f, 0.0f,  2000.0f });

	itr2 = positionList.begin();   //イテレータを先頭に設定
}

/// <summary>
/// 描画処理
/// </summary>
void ThirdStageMap::Draw()
{
	MV1DrawModel(modelHandle);
}