#pragma once

#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// �G�t�F�N�g���N���X
/// </summary>
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	virtual void Update(VECTOR position) = 0;		//�X�V����
	virtual void Draw() = 0;						//�`�揈��

protected:

	int effectHandle;				//�G�t�F�N�g�n���h��
	int playingEffectHandle;		//�Đ����̃G�t�F�N�g�̃n���h����������
	int effectTime;					//�G�t�F�N�g����

	//�萔
	const int PLAY_EFFECT_TIME;		//�G�t�F�N�g�Đ�����
	const int INITIAL_EFFECT_TIME;	//�����G�t�F�N�g�Đ�����

private:
	EffectBase(const EffectBase&);	//�R�s�[�R���X�g���N�^
};