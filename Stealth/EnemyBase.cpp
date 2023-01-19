#include "EnemyBase.h"


const float EnemyBase::SPEED	= 1000.0f;						//�ړ����x
const float EnemyBase::RANGE_DEGREE = 45.0f;					//����p�x


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
	//�����Ȃ�
}

EnemyBase::~EnemyBase()
{
	//�����Ȃ�
}