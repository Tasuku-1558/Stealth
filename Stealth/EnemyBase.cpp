#include "EnemyBase.h"


/// <summary>
/// �R���X�g���N�^
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
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBase::~EnemyBase()
{
	//�����Ȃ�
}