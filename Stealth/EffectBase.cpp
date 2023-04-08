#include "EffectBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
EffectBase::EffectBase()
	: effectHandle(0)
	, playingEffectHandle(0)
	, effectTime(0)
	, PLAY_EFFECT_TIME(1)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
EffectBase::~EffectBase()
{
	//処理なし
}