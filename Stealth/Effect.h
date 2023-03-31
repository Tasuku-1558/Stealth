#pragma once

#include "EffectBase.h"

/// <summary>
/// �G�t�F�N�g�N���X
/// </summary>
class Effect final : public EffectBase
{
public:
	Effect(string effectPath, float effectSize);
	virtual ~Effect();

	void Update(VECTOR position)override;	//�X�V����
	void Draw()override;					//�`�揈��

private:

	Effect(const Effect&);	//�R�s�[�R���X�g���N�^
};