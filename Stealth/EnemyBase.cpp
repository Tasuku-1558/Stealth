#include "EnemyBase.h"


const float EnemyBase::SPEED	= 900.0f;						//移動速度
const float EnemyBase::RANGE_DEGREE = 45.0f;					//視野角度


EnemyBase::EnemyBase()
	: speed(0.0f)
	, object()
	, targetPosition()
	, length(900.0f)
	, discovery(false)
	, playerFindCount(0)
	, findImage(0)
	, viewRangeImage(0)
	, markImage(0)
	, discoverySE(0)
{
	//処理なし
}

EnemyBase::~EnemyBase()
{
	//処理なし
}