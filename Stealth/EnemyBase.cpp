#include "EnemyBase.h"


const float EnemyBase::SPEED		= 1000.0f;					//�ړ����x
const float EnemyBase::RANGE_DEGREE = 45.0f;					//����p�x

/// <summary>
/// �R���X�g���N�^
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
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBase::~EnemyBase()
{
	//�����Ȃ�
}