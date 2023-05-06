#include "CakeParticle.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="particlePosition">�p�[�e�B�N���̈ʒu</param>
CakeParticle::CakeParticle(const VECTOR& particlePosition)
	: PINK(GetColor(224, 148, 171))
	, MAX_POP_TIME(2.0f)
	, POSITION_Y(0.0f)
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

	position.y = POSITION_Y;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void CakeParticle::Update(float deltaTime)
{
	//�p�[�e�B�N���̔��a�𒲐�����
	radius = ((MAX_POP_TIME - particlePopCount) / MAX_POP_TIME) * radius;

	//�p�[�e�B�N���ɔ�΂��͂�������
	position.x += xPower;
	position.z += zPower;
	
	//�p�[�e�B�N�����o������J�E���g���J�n����
	particlePopCount += deltaTime;

	//�p�[�e�B�N���̏o�����Ԃ𒴂�����
	if (particlePopCount > MAX_POP_TIME)
	{
		endFlag = true;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void CakeParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA);
	DrawSphere3D(position, radius, DIVNUM, PINK, PINK, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NOBLEND);
}

/// <summary>
/// �폜����
/// </summary>
void CakeParticle::DeleteParticle()
{
	endFlag = false;

	particlePopCount = INITIAL_PARTICLE_POP_COUNT;
}