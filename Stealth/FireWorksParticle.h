#pragma once

#include "DxLib.h"
#include "ParticleBase.h"

/// <summary>
/// �ԉ΃p�[�e�B�N���N���X
/// ���U���g��ʂŏo���p�[�e�B�N��
/// </summary>
class FireWorksParticle final : public ParticleBase
{
public:
	FireWorksParticle(const VECTOR pos, unsigned int changeColor);
	virtual ~FireWorksParticle();

	void Initialize()override;				//����������
	void Activate()override;				//����������
	void Update(float deltaTime)override;	//�X�V����
	void Draw()override;					//�`�揈��

private:
	FireWorksParticle(const FireWorksParticle&);	//�R�s�[�R���X�g���N�^


	float particlePopTime;				//�p�[�e�B�N���̏o������
	unsigned int color;					//�p�[�e�B�N���̐F
};