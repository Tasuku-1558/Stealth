#include "ParticleBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ParticleBase::ParticleBase()
	: radius(50.0f)
	, particleCount(0.0f)
	, xPower(0.0f)
	, zPower(0.0f)
	, endFlag(false)
	, position()
	, DIVNUM(8)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ParticleBase::~ParticleBase()
{
	//�����Ȃ�
}