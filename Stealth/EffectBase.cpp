#include "EffectBase.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectBase::EffectBase()
	: effectHandle(0)
	, playingEffectHandle(0)
	, effectTime(0)
	, PLAY_EFFECT_TIME(1)
	, INITIAL_EFFECT_TIME(0)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectBase::~EffectBase()
{
	//�����Ȃ�
}