#include "FireWorksParticle.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="particlePosition"></param>
/// <param name="changeColor"></param>
FireWorksParticle::FireWorksParticle(const VECTOR particlePosition, unsigned int changeColor)
	: particlePopTime(3.0f)
	, color(0)
	, POS_Y(1000.0f)
{
	position = particlePosition;

	color = changeColor;

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
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void FireWorksParticle::Update(float deltaTime)
{
	//�p�[�e�B�N���̔��a�𒲐�����
	radius = ((particlePopTime - particleCount) / particlePopTime) * radius;

	//�p�[�e�B�N���ɔ�΂��͂�������
	position.x += xPower;
	position.y = POS_Y;
	position.z += zPower;

	//�p�[�e�B�N�����o������J�E���g���J�n����
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
void FireWorksParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawSphere3D(position, radius, DIVNUM, color, color, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}