#include "ParticleBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
ParticleBase::ParticleBase()
	: radius(50.0f)
	, particlePopCount(0.0f)
	, xPower(0.0f)
	, zPower(0.0f)
	, endFlag(false)
	, position()
	, DIVNUM(8)
	, ALPHA(128)
	, NOBLEND(255)
	, INITIAL_PARTICLE_POP_COUNT(0.0f)
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