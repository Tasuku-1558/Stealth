#include "CakeParticle.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="particlePosition">�p�[�e�B�N���̈ʒu</param>
CakeParticle::CakeParticle(const VECTOR& particlePosition)
	: PINK(GetColor(224, 148, 171))
	, PARTICLE_POP_TIME(2.0f)
	, POS_Y(0.0f)
{
	position = particlePosition;

	Initialize();
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
	//�p�[�e�B�N�����΂��͂������_���l�ɂ���
	float rad = (float)(rand() % 200) / 100.0f;
	float tmpRadius = (float)(rand() % 100) / 10.0f;

	xPower = tmpRadius * cosf(rad * DX_PI_F);
	zPower = tmpRadius * sinf(rad * DX_PI_F);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void CakeParticle::Update(float deltaTime)
{
	//�p�[�e�B�N���̔��a�𒲐�����
	radius = ((PARTICLE_POP_TIME - particleCount) / PARTICLE_POP_TIME) * radius;

	//�p�[�e�B�N���ɔ�΂��͂�������
	position.x += xPower;
	position.y = POS_Y;
	position.z += zPower;
	
	//�p�[�e�B�N�����o������J�E���g���J�n����
	particleCount += deltaTime;

	//�p�[�e�B�N���̏o�����Ԃ𒴂�����p�[�e�B�N��������
	if (particleCount > PARTICLE_POP_TIME)
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
	DrawSphere3D(position, radius, DIVNUM, PINK, PINK, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}