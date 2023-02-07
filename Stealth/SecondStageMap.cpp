#include "SecondStageMap.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR SecondStageMap::SIZE	  = { 80.0f, 60.0f, 80.0f };				//モデルの倍率
const VECTOR SecondStageMap::POSITION = { -7000.0f, -100.0f, -2900.0f };		//モデルの位置

using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
SecondStageMap::SecondStageMap() : StageBase()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SecondStageMap::~SecondStageMap()
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
void SecondStageMap::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE2));
	MV1SetScale(modelHandle, SIZE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [STAGE2]\n");
	}

	MapList();
	MapList2();
}

/// <summary>
/// 終了処理
/// </summary>
void SecondStageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// 敵の行動パターンリスト(壁の周りを回る敵)
/// </summary>
void SecondStageMap::MapList()
{
	positionList.push_back({ -2200.0f, 0.0f, 600.0f });
	positionList.push_back({ -2200.0f, 0.0f, -700.0f });
	positionList.push_back({ -1400.0f, 0.0f, -700.0f });
	positionList.push_back({ -1400.0f, 0.0f, 600.0f });

	itr = positionList.begin();		//イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト2(上下移動の敵)
/// </summary>
void SecondStageMap::MapList2()
{
	positionList2.push_back({ -5000.0f, 0.0f, 0.0f });
	positionList2.push_back({ -4400.0f, 0.0f, 0.0f });

	itr2 = positionList2.begin();   //イテレータを先頭に設定
}

/// <summary>
/// 描画処理
/// </summary>
void SecondStageMap::Draw()
{
	MV1DrawModel(modelHandle);
}