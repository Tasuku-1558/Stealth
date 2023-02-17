#include <math.h>
#include "FireWorksParticle.h"


const unsigned int FireWorksParticle::ORANGE = GetColor(255, 255, 0);		//�p�[�e�B�N���̃J���[


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
FireWorksParticle::FireWorksParticle(const VECTOR pos, unsigned int changeColor)
	: position()
	, radius(50.0f)
	, particleCount(0.0f)
	, particlePopTime(3.0f)
	, endFlag(false)
	, xPower(0.0f)
	, zPower(0.0f)
	, color(0)
{
	position = pos;

	color = changeColor;

	Initialize();
	Activate();
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
	//�p�[�e�B�N�����΂��͂������_���l��
	float rad = (float)(rand() % 200) / 100.0f;
	float tmpRadius = (float)(rand() % 100) / 10.0f;

	xPower = tmpRadius * cosf(rad * DX_PI_F);
	zPower = tmpRadius * sinf(rad * DX_PI_F);
}

/// <summary>
/// ����������
/// </summary>
void FireWorksParticle::Activate()
{
	particleCount = 0.0f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void FireWorksParticle::Update(float deltaTime)
{
	radius = ((particlePopTime - particleCount) / particlePopTime) * radius;
	position.x += xPower;
	position.y = 1000.0f;
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
void FireWorksParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawSphere3D(position, radius, 8, color, color, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}