#include "EnemyBase.h"


const float EnemyBase::SPEED	= 900.0f;						//移動速度
const float EnemyBase::RANGE_DEGREE = 45.0f;					//視野角度


EnemyBase::EnemyBase()
	: speed(0.0f)
{
	//処理なし
}

EnemyBase::~EnemyBase()
{
	//処理なし
}