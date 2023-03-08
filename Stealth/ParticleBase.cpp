#include "ParticleBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
ParticleBase::ParticleBase()
	: position()
	, radius(50.0f)
	, particleCount(0.0f)
	, xPower(0.0f)
	, zPower(0.0f)
	, endFlag(false)
	, DIVNUM(8)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ParticleBase::~ParticleBase()
{
	//処理なし
}