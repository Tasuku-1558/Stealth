#pragma once

#include "EffectBase.h"
#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// ���X�|�[���G�t�F�N�g�N���X
/// �P�[�L�ăX�|�[�����̃G�t�F�N�g�ƃv���C���[���X�|�[�����̃G�t�F�N�g�Ɏg�p���Ă���
/// </summary>
class RepopEffect final : public EffectBase
{
public:
	RepopEffect(/*string effectPath, float effectSize*/);
	virtual ~RepopEffect();

	void Update(VECTOR pos)override;	//�X�V����
	void Draw()override;				//�`�揈��

private:

	RepopEffect(const RepopEffect&);	//�R�s�[�R���X�g���N�^

	//�萔
	const string EFFECT_FOLDER_PATH;	//effect�t�H���_�܂ł̃p�X
	const string CAKE_PATH;				//�P�[�L�ăX�|�[�����G�t�F�N�g�̃p�X
	const float  MAGNIFICATION;			//�G�t�F�N�g�̊g�嗦
};