#include "Light.h"


const VECTOR Light::DIRECTION = { 0.0f,-1.0f,0.0f };	//ƒ‰ƒCƒg‚Ì•ûŒü

Light::Light()
{
	//ˆ—‚È‚µ
}

Light::~Light()
{
	//ˆ—‚È‚µ
}

void Light::Initialize()
{
	SetLightDirection(DIRECTION);
}