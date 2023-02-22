#include "CakeParticle.h"
#include <math.h>


//const unsigned int CakeParticle::PINK = GetColor(224, 148, 171);		//�p�[�e�B�N���̃J���[


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
CakeParticle::CakeParticle(const VECTOR& pos)
	: position()
	, radius(30.0f)
	, particleCount(0.0f)
	, particlePopTime(5.0f)
	, endFlag(false)
	, xPower(0.0f)
	, zPower(0.0f)
	, PINK(GetColor(224, 148, 171))
{
	position = pos;

	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CakeParticle::~CakeParticle()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void CakeParticle::Initialize()
{
	//�p�[�e�B�N�����΂��͂������_���l��
	float rad = (float)(rand() % 200) / 100.0f;
	float tmpRadius = (float)(rand() % 100) / 10.0f;

	xPower = tmpRadius * cosf(rad * DX_PI_F);
	zPower = tmpRadius * sinf(rad * DX_PI_F);
}

/// <summary>
/// ����������
/// </summary>
void CakeParticle::Activate()
{
	particleCount = 0.0f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void CakeParticle::Update(float deltaTime)
{
	radius = ((particlePopTime - particleCount) / particlePopTime) * radius;
	position.x += xPower;
	position.y = 0.0f;
	position.z += zPower;
	
	particleCount += deltaTime;

	//�p�[�e�B�N���̏o�����Ԃ𒴂�����p�[�e�B�N��������
	if (particleCount > particlePopTime)
	{
		endFlag = true;

		particleCount = 0.0f;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void CakeParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawSphere3D(position, radius, 8, PINK, PINK, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}