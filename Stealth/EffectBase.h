#pragma once

#include "DxLib.h"

/// <summary>
/// �G�t�F�N�g�x�[�X�N���X
/// </summary>
class EffectBase
{
public:
	EffectBase() {/*�����Ȃ�*/ };
	virtual ~EffectBase() {/*�����Ȃ�*/ };

	virtual void Initialize() = 0;				//����������
	virtual void Finalize() = 0;				//�I������
	virtual void Activate() = 0;				//����������
	virtual void Update(VECTOR pos) = 0;		//�X�V����
	virtual void Draw() = 0;					//�`�揈��

private:
	EffectBase(const EffectBase&);		//�R�s�[�R���X�g���N�^
};