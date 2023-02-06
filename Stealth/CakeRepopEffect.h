#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// �P�[�L�G�t�F�N�g�N���X
/// �P�[�L�ăX�|�[�����̃G�t�F�N�g
/// </summary>
class CakeRepopEffect final : public EffectBase
{
public:
	CakeRepopEffect();
	virtual ~CakeRepopEffect();

	void Initialize();		//����������
	void Activate();		//����������

	void Update(float cakePosX, float cakePosY, float cakePosZ);			//�X�V����
	void Draw();															//�`�揈��

private:

	CakeRepopEffect(const CakeRepopEffect&);		//�R�s�[�R���X�g���N�^
	void Finalize();								//�I������


	int effectHandle;				//�P�[�L�ăX�|�[�����G�t�F�N�g�i�[�p
	int effectTime;					//�G�t�F�N�g����

	//�P�[�L�ăX�|�[�����G�t�F�N�g�̈ʒu
	float effectPosX;
	float effectPosY;
	float effectPosZ;

	int playingEffectHandle;		// �Đ����̃G�t�F�N�g�̃n���h����������

	//�ÓI�萔
	static const string EFFECT_FOLDER_PATH;		//effect�t�H���_�܂ł̃p�X
	static const string CAKE_PATH;				//�P�[�L�ăX�|�[�����G�t�F�N�g�̃p�X
};