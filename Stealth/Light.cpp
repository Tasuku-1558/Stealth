#include "Light.h"


const VECTOR Light::DIRECTION = { 0.0f,-1.0f,0.0f };	//ライトの方向

Light::Light()
{
	//処理なし
}

Light::~Light()
{
	//処理なし
}

void Light::Initialize()
{
	SetLightDirection(DIRECTION);
}