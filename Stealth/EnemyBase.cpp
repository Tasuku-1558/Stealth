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
	, playerDirection(0.0f)
	, bulletDirection(0.0f)
	, rotateTime(0.0f)
	, playerSpotted(false)
	, cakeFlag(false)
	, targetPosition()
	, visualPosition()
	, visualDir()
	, ROTATE_TIME_CATEGORY(3)
	, RANGE_DEGREE(27.0f)
	, TARGET_ANGLE(0.0f)
	, INITIAL_ROTATE_TIME(0.0f)
	, RADIUS(100.0f)
	, Y_ANGLE(0.0f)
	, Y_ANGLE_SPEED(4.0f)
	, NOMAL_ROTATE_TIME(1.0f)
	, PLAYER_ROTATE_TIME(2.0f)
	, CAKE_ROTATE_TIME(6.0f)
	, STOP_SPEED(0.0f)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, MARK_PATH("mark.png")
{
	MapList();
	MapList2();
	MapList3();
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