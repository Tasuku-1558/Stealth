#include "ParticleBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ParticleBase::ParticleBase()
	: radius(50.0f)
	, particlePopCount(0.0f)
	, xPower(0.0f)
	, zPower(0.0f)
	, endFlag(false)
	, position()
	, DIVNUM(8)
	, ALPHA(128)
	, NOBLEND(255)
	, INITIAL_PARTICLE_POP_COUNT(0.0f)
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