#include "Light.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Light::Light()
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Light::~Light()
{
	//�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
void Light::Update(VECTOR direction)
{
	SetLightDirection(direction);
}