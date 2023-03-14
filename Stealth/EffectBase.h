#pragma once

#include "DxLib.h"

/// <summary>
/// �G�t�F�N�g�x�[�X�N���X
/// </summary>
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	virtual void Update(VECTOR position) = 0;		//�X�V����
	virtual void Draw() = 0;						//�`�揈��

protected:

	int effectHandle;					//�G�t�F�N�g�n���h��
	int playingEffectHandle;			//�Đ����̃G�t�F�N�g�̃n���h����������
	int effectTime;						//�G�t�F�N�g����

private:
	EffectBase(const EffectBase&);		//�R�s�[�R���X�g���N�^
};