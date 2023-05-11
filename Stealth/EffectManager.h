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
		SHOT,				//�P�[�L���˃G�t�F�N�g
		EFFECT_AMOUNT,		//�G�t�F�N�g�̎��
	};

	void Draw();			//�`�揈��

	void CreateEffect(VECTOR position, EffectType effectType);	//�G�t�F�N�g�̐���

private:
	EffectManager(const EffectManager&);	//�R�s�[�R���X�g���N�^

	void Initialize();					//����������
	void DeleteEffect();				//�G�t�F�N�g�̍폜

	EffectBase* effect[EFFECT_AMOUNT];	//�G�t�F�N�g�i�[�p

	struct Effects
	{
		string effectPath;	//�G�t�F�N�g�̃p�X
		float  effectSize;	//�G�t�F�N�g�̃T�C�Y
	};

	//�G�t�F�N�g
	const string EFFECT_FOLDER_PATH;	//Effect�t�H���_�܂ł̃p�X
	const string RESPAWN_EFFECT_PATH;	//���X�|�[���G�t�F�N�g�̃p�X
	const string SHOT_EFFECT_PATH;		//�P�[�L���˃G�t�F�N�g�̃p�X

	//�G�t�F�N�g�̃T�C�Y
	const float  RESPAWN_SIZE;			//���X�|�[���G�t�F�N�g�̃T�C�Y
	const float  SHOT_SIZE;				//�P�[�L���˃G�t�F�N�g�̃T�C�Y

};