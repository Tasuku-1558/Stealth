#include "EnemyBase.h"


const float EnemyBase::SPEED		= 1000.0f;					//移動速度
const float EnemyBase::RANGE_DEGREE = 45.0f;					//視野角度

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase()
	: speed(0.0f)
	, object()
	, targetPosition()
	, length(900.0f)
	, playerSpotted(false)
	, cakeFlag(false)
	, playerFindCount(0)
	, playerFindImage(0)
	, markImage(0)
	, spottedSE(0)
	, cakeEatImage(0)
	, visualModelHandle(0)
	, visualPosition()
	, visualDir()
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