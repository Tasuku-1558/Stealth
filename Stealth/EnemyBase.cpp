#include "EnemyBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase()
	: targetPosition()
	, visualPosition()
	, visualDir()
	, markImage(0)
	, cakeImage()
	, visualModelHandle(0)
	, speed(0.0f)
	, changeSpeed(0.0f)
	, length(900.0f)
	, bulletDirection(0.0f)
	, playerSpotted(false)
	, cakeFlag(false)
	, RANGE_DEGREE(27.0f)
	, RADIUS(100.0f)
	, CAKE_IMAGE_NUMBER(2)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{
	//処理なし
}