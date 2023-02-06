#include "EnemyBase.h"


const float EnemyBase::SPEED			 = 1000.0f;			//�ړ����x
const float EnemyBase::RANGE_DEGREE		 = 45.0f;			//����p�x
const int	EnemyBase::CAKE_IMAGE_NUMBER = 2;				//�P�[�L�摜��

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBase::EnemyBase()
	: speed(0.0f)
	, object()
	, targetPosition()
	, length(900.0f)
	, bulletDirection(0.0f)
	, playerSpotted(false)
	, cakeFlag(false)
	, playerFindImage(0)
	, markImage(0)
	, cakeImage()
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