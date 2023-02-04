#include "CakeParticle.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
CakeParticle::CakeParticle(VECTOR pos)
	: position()
	, radius(200.0f)
	, particleCount(0.0f)
	, particlePopTime(2.0f)
	, endFlag(false)
	, xPower(0.0f)
	, yPower(0.0f)
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
	xPower = -0.5f  + ((float)(rand() % 20) / 20.0f);
	yPower = -0.25f + ((float)(rand() % 20) / 40.0f);
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
	position.y += yPower;
	position.z = 0.0f;
	
	particleCount += deltaTime;

	if (particleCount > particlePopTime)
	{
		endFlag = true;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void CakeParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawSphere3D(position, radius, 8, GetColor(139, 69, 19), GetColor(139, 69, 19), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}