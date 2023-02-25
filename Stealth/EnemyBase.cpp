#include "EnemyBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase()
	: speed(0.0f)
	, changeSpeed(0.0f)
	, targetPosition()
	, length(900.0f)
	, bulletDirection(0.0f)
	, playerSpotted(false)
	, cakeFlag(false)
	, markImage(0)
	, cakeImage()
	, visualModelHandle(0)
	, visualPosition()
	, visualDir()
	, RANGE_DEGREE(27.0f)
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