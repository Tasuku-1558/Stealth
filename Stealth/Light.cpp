#include "Light.h"


const VECTOR Light::DIRECTION = { 0.0f,-0.5f,0.0f };	//���C�g�̕���


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
/// ����������
/// </summary>
void Light::Initialize()
{
	SetLightDirection(DIRECTION);	
}