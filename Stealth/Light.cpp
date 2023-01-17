#include "Light.h"


const VECTOR Light::DIRECTION = { 0.0f,-0.5f,0.0f };	//ƒ‰ƒCƒg‚Ì•ûŒü

Light::Light()
	: lightHandle(0)
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

void Light::Update(VECTOR enemyDir)
{
	//lightHandle = CreateDirLightHandle(enemyDir);

}