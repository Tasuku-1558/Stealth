#include "StageMap.h"


using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelType"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
/// <param name="position"></param>
StageMap::StageMap(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position)
	: StageBase()
	, stageNo(0)
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	MV1SetScale(modelHandle, size);
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// デストラクタ
/// </summary>
StageMap::~StageMap()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void StageMap::Initialize()
{
	stageNo = 1;

	//エネミーの行動パターンリスト
	MapList();
	MapList2();
	MapList3();
	MapList4();
	MapList5();
	MapList6();
	MapList7();
	MapList8();
	MapList9();

}

/// <summary>
/// 終了処理
/// </summary>
void StageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 描画処理
/// </summary>
void StageMap::Draw()
{
	MV1DrawModel(modelHandle);
	DrawFormatString(500, 100, GetColor(255, 0, 0), "StageNo : %d", stageNo);
}

/// <summary>
/// 敵の行動パターンリスト(左右移動の敵)
/// FirstStageの敵
/// </summary>
void StageMap::MapList()
{
	positionList[0].push_back({ -3200.0f, 0.0f, 1000.0f });
	positionList[0].push_back({ -3200.0f, 0.0f, -1000.0f });

	itr[0] = positionList[0].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト2(壁の周りを回る敵)
/// SecondStageの敵
/// </summary>
void StageMap::MapList2()
{
	positionList[1].push_back({ -2200.0f, 0.0f, 600.0f });
	positionList[1].push_back({ -2200.0f, 0.0f, -700.0f });

	//positionList[1].push_back({ -2100.0f, 0.0f, -800.0f });

	positionList[1].push_back({ -1400.0f, 0.0f, -700.0f });
	positionList[1].push_back({ -1400.0f, 0.0f, 600.0f });

	/*positionList[1].push_back({ -1400.0f, 0.0f, -700.0f });
	positionList[1].push_back({ -1400.0f, 0.0f, 600.0f });*/

	itr[1] = positionList[1].begin();	//イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト3(上下移動の敵)
/// SecondStageの敵
/// </summary>
void StageMap::MapList3()
{
	positionList[2].push_back({ -5000.0f, 0.0f, 0.0f });
	positionList[2].push_back({ -4400.0f, 0.0f, 0.0f });

	itr[2] = positionList[2].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト4(上下移動の敵)
/// ThirdStageの敵
/// </summary>
void StageMap::MapList4()
{
	positionList[3].push_back({ -2500.0f, 0.0f, 800.0f });
	positionList[3].push_back({ -1500.0f, 0.0f, 800.0f });

	itr[3] = positionList[3].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト5(ゴールの位置を塞ぐ敵)
/// ThirdStageの敵
/// </summary>
void StageMap::MapList5()
{
	positionList[4].push_back({ -2500.0f, 0.0f,  5000.0f });
	positionList[4].push_back({ -2500.0f, 0.0f,  4300.0f });
	positionList[4].push_back({ -2800.0f, 0.0f,  4300.0f });
	positionList[4].push_back({ -2500.0f, 0.0f,  4300.0f });

	itr[4] = positionList[4].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト6(左右移動の敵)
/// FourthStageの敵
/// </summary>
void StageMap::MapList6()
{
	positionList[5].push_back({ -1300.0f, 0.0f, 500.0f });
	positionList[5].push_back({ -1300.0f, 0.0f, -700.0f });

	itr[5] = positionList[5].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト7(壁の周りを回る敵)
/// FourthStageの敵
/// </summary>
void StageMap::MapList7()
{
	positionList[6].push_back({ -4800.0f, 0.0f, -500.0f });
	positionList[6].push_back({ -4800.0f, 0.0f, -1500.0f });
	positionList[6].push_back({ -3800.0f, 0.0f, -1500.0f });
	positionList[6].push_back({ -3800.0f, 0.0f, -500.0f });

	itr[6] = positionList[6].begin();	//イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト8(右下L字移動の敵)
/// FifthStageの敵
/// </summary>
void StageMap::MapList8()
{
	positionList[7].push_back({ -2300.0f, 0.0f, 3300.0f });
	positionList[7].push_back({ -620.0f, 0.0f, 3300.0f });
	positionList[7].push_back({ -620.0f, 0.0f, 2800.0f });
	positionList[7].push_back({ -620.0f, 0.0f, 3300.0f });

	itr[7] = positionList[7].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト9(左上L字移動の敵)
/// FifthStageの敵
/// </summary>
void StageMap::MapList9()
{
	positionList[8].push_back({ -2200.0f, 0.0f, 2200.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2200.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2800.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2200.0f });

	itr[8] = positionList[8].begin();   //イテレータを先頭に設定
}