#include "Light.h"


const VECTOR Light::DIRECTION = { 0.0f,-0.5f,0.0f };	//���C�g�̕���

Light::Light()
{
	//�����Ȃ�
}

Light::~Light()
{
	//�����Ȃ�
}

void Light::Initialize()
{
	SetLightDirection(DIRECTION);
}