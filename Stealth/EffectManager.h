#pragma once

#include "EffectBase.h"

/// <summary>
/// �G�t�F�N�g�Ǘ��N���X
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	virtual ~EffectManager();

	//�G�t�F�N�g�̎��
	enum EffectType
	{
		RESPAWN,			//���X�|�[���G�t�F�N�g
		EFFECT_AMOUNT,		//�G�t�F�N�g�̎��
	};

	void Draw();			//�`�揈��

	void CreateEffect(VECTOR position, EffectType effectType);	//�G�t�F�N�g�̐���

private:
	EffectManager(const EffectManager&);		//�R�s�[�R���X�g���N�^

	void Initialize();							//����������

	EffectBase* effect[EFFECT_AMOUNT];			//�G�t�F�N�g�i�[�p

	//�G�t�F�N�g
	const string EFFECT_FOLDER_PATH;	//Effect�t�H���_�܂ł̃p�X
	const string RESPAWN_EFFECT_PATH;	//���X�|�[���G�t�F�N�g�̃p�X

	//�G�t�F�N�g�̃T�C�Y
	const float  RESPAWN_SIZE;			//���X�|�[���G�t�F�N�g�̃T�C�Y

};