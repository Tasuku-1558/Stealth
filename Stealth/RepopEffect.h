#pragma once

#include "EffectBase.h"
#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// ���X�|�[���G�t�F�N�g�N���X
/// �P�[�L�ăX�|�[�����̃G�t�F�N�g�ƃv���C���[���X�|�[�����̃G�t�F�N�g
/// </summary>
class RepopEffect final : public EffectBase
{
public:
	RepopEffect();
	virtual ~RepopEffect();

	void Initialize();			//����������
	void Activate();			//����������
	void Update(VECTOR pos);	//�X�V����
	void Draw();				//�`�揈��

private:

	RepopEffect(const RepopEffect&);		//�R�s�[�R���X�g���N�^
	void Finalize();								//�I������

	int effectHandle;					//�P�[�L�ăX�|�[�����G�t�F�N�g�i�[�p
	int effectTime;						//�G�t�F�N�g����

	int playingEffectHandle;			//�Đ����̃G�t�F�N�g�̃n���h����������

	//�萔
	const string EFFECT_FOLDER_PATH;	//effect�t�H���_�܂ł̃p�X
	const string CAKE_PATH;				//�P�[�L�ăX�|�[�����G�t�F�N�g�̃p�X
};