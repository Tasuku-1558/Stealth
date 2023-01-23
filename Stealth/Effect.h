#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// �{�[���G�t�F�N�g�N���X
/// �{�[���ăX�|�[�����̃G�t�F�N�g
/// </summary>
class Effect final : public EffectBase
{
public:
	Effect();
	virtual ~Effect();

	void Initialize();		//����������
	void Finalize();		//�I������
	void Activate();		//����������

	void Update(float ballPosX, float ballPosY, float ballPosZ);			//�X�V����
	void Draw();															//�`�揈��

private:

	int effectHandle;				//�{�[���ăX�|�[�����G�t�F�N�g�i�[�p
	int effectTime;					//�G�t�F�N�g����

	//�{�[���ăX�|�[�����G�t�F�N�g�̈ʒu
	float effectPos_X;
	float effectPos_Y;
	float effectPos_Z;

	int playingEffectHandle;		// �Đ����̃G�t�F�N�g�̃n���h����������


	//�ÓI�萔
	static const string EFFECT_FOLDER_PATH;		//effect�t�H���_�܂ł̃p�X
	static const string BALL_PATH;				//�{�[���ăX�|�[�����G�t�F�N�g�̃p�X

};