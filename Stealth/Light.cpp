#include "Light.h"


/// <summary>
/// コンストラクタ
/// </summary>
Light::Light()
	: DIRECTION({ 0.0f,-0.5f,0.0f })
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Light::~Light()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Light::Initialize()
{
	//ライトの向きを設定
	SetLightDirection(DIRECTION);
}