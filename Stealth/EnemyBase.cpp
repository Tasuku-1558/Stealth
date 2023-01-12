#include "EnemyBase.h"


const float EnemyBase::SPEED	= 900.0f;						//ˆÚ“®‘¬“x
const float EnemyBase::RANGE_DEGREE = 45.0f;					//‹–ìŠp“x


EnemyBase::EnemyBase()
	: speed(0.0f)
	, object()
	, targetPosition()
	, length(400.0f)
	, discovery(false)
	, playerFindCount(0)
	, findImage(0)
	, viewRangeImage(0)
	, markImage(0)
	, discoverySE(0)
	, ballFlag(false)
	, count(0)
{
	//ˆ—‚È‚µ
}

EnemyBase::~EnemyBase()
{
	//ˆ—‚È‚µ
}