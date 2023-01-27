#include "Light.h"


/// <summary>
/// コンストラクタ
/// </summary>
Light::Light()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Light::~Light()
{
	//処理なし
}

/// <summary>
/// 更新処理
/// </summary>
void Light::Update(VECTOR direction)
{
	SetLightDirection(direction);
}