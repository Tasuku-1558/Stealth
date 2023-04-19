#include "FireWorksParticle.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="particlePosition">�p�[�e�B�N���̈ʒu</param>
/// <param name="particleColor">�p�[�e�B�N���̐F</param>
FireWorksParticle::FireWorksParticle(const VECTOR& particlePosition, unsigned int particleColor)
	: color(0)
	, MAX_POP_TIME(3.0f)
	, POSITION_Y(1000.0f)
{
	position = particlePosition;

	color = particleColor;

	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FireWorksParticle::~FireWorksParticle()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void FireWorksParticle::Initialize()
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
void FireWorksParticle::Update(float deltaTime)
{
	//�p�[�e�B�N���̔��a�𒲐�����
	radius = ((MAX_POP_TIME - particlePopCount) / MAX_POP_TIME) * radius;

	//�p�[�e�B�N���ɔ�΂��͂�������
	position.x += xPower;
	position.z += zPower;

	//�p�[�e�B�N�����o������J�E���g���J�n����
	particlePopCount += deltaTime;

	//�p�[�e�B�N���̏o�����Ԃ𒴂�����p�[�e�B�N��������
	if (particlePopCount > MAX_POP_TIME)
	{
		endFlag = true;

		particlePopCount = INITIAL_PARTICLE_POP_COUNT;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void FireWorksParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA);
	DrawSphere3D(position, radius, DIVNUM, color, color, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NOBLEND);
}