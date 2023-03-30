#pragma once

#include "EffectBase.h"
#include <string>


using namespace std;

/// <summary>
/// �G�t�F�N�g�Ǘ��N���X
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	virtual ~EffectManager();

	//�G�t�F�N�g�̎��
	enum Effect
	{
		REPOP,				//���X�|�[���G�t�F�N�g(�P�[�L�ƃv���C���[)
		EFFECT_AMOUNT,		//�G�t�F�N�g�̎��
	};

	void Draw();			//�`�揈��

	void CreateRepopEffect(VECTOR position);	//���X�|�[���G�t�F�N�g�̐���

private:
	EffectManager(const EffectManager&);		//�R�s�[�R���X�g���N�^

	void Initialize();							//����������

	string InputPath(string folderPath, 
					 string effectPath);		//�p�X�̓���


	EffectBase* effect[EFFECT_AMOUNT];			//�G�t�F�N�g�i�[�p


	//�G�t�F�N�g
	const string EFFECT_FOLDER_PATH;	//Effect�t�H���_�܂ł̃p�X
	const string REPOP_EFFECT_PATH;		//���X�|�[�����G�t�F�N�g�̃p�X

	//�G�t�F�N�g�̃T�C�Y
	const float  REPOP_SIZE;			//���X�|�[���G�t�F�N�g�̃T�C�Y

};