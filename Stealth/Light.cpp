#include "Light.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Light::Light()
	: DIRECTION({ 0.0f,-0.5f,0.0f })
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
/// ����������
/// </summary>
void Light::Initialize()
{
	SetLightDirection(DIRECTION);
}