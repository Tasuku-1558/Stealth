#include "EnemyBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase()
	: markImage(0)
	, visualModelHandle(0)
	, speed(0.0f)
	, changeSpeed(0.0f)
	, length(900.0f)
	, bulletDirection(0.0f)
	, playerSpotted(false)
	, cakeFlag(false)
	, targetPosition()
	, visualPosition()
	, visualDir()
	, RANGE_DEGREE(27.0f)
	, RADIUS(100.0f)
{
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
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{
	//処理なし
}

/// <summary>
/// 敵の行動パターンリスト(左右移動の敵)
/// FirstStageの敵
/// </summary>
void EnemyBase::MapList()
{
	positionList[0].push_back({ 1000.0f, 0.0f, 2900.0f });
	positionList[0].push_back({ -1000.0f, 0.0f, 2900.0f });

	itr[0] = positionList[0].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト2(壁の周りを回る敵)
/// SecondStageの敵
/// </summary>
void EnemyBase::MapList2()
{
	positionList[1].push_back({ -2200.0f, 0.0f, 600.0f });
	positionList[1].push_back({ -2200.0f, 0.0f, -700.0f });
	positionList[1].push_back({ -1400.0f, 0.0f, -700.0f });
	positionList[1].push_back({ -1400.0f, 0.0f, 600.0f });

	itr[1] = positionList[1].begin();	//イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト3(上下移動の敵)
/// SecondStageの敵
/// </summary>
void EnemyBase::MapList3()
{
	positionList[2].push_back({ -5000.0f, 0.0f, 0.0f });
	positionList[2].push_back({ -4400.0f, 0.0f, 0.0f });

	itr[2] = positionList[2].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト4(上下移動の敵)
/// ThirdStageの敵
/// </summary>
void EnemyBase::MapList4()
{
	positionList[3].push_back({ -2500.0f, 0.0f, 800.0f });
	positionList[3].push_back({ -1500.0f, 0.0f, 800.0f });

	itr[3] = positionList[3].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト5(ゴールの位置を塞ぐ敵)
/// ThirdStageの敵
/// </summary>
void EnemyBase::MapList5()
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
void EnemyBase::MapList6()
{
	positionList[5].push_back({ -1300.0f, 0.0f, 500.0f });
	positionList[5].push_back({ -1300.0f, 0.0f, -700.0f });

	itr[5] = positionList[5].begin();   //イテレータを先頭に設定
}

/// <summary>
/// 敵の行動パターンリスト7(壁の周りを回る敵)
/// FourthStageの敵
/// </summary>
void EnemyBase::MapList7()
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
void EnemyBase::MapList8()
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
void EnemyBase::MapList9()
{
	positionList[8].push_back({ -2200.0f, 0.0f, 2200.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2200.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2800.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2200.0f });

	itr[8] = positionList[8].begin();   //イテレータを先頭に設定
}