#pragma once

#include "ParticleBase.h"

/// <summary>
/// �ԉ΃p�[�e�B�N���N���X
/// ���U���g��ʂŏo���p�[�e�B�N��
/// </summary>
class FireWorksParticle final : public ParticleBase
{
public:
	FireWorksParticle(const VECTOR& particlePosition, unsigned int particleColor);
	virtual ~FireWorksParticle();

	void Update(float deltaTime)override;	//�X�V����
	void Draw()override;					//�`�揈��
	void DeleteParticle()override;			//�폜����

private:
	FireWorksParticle(const FireWorksParticle&);	//�R�s�[�R���X�g���N�^

	void Initialize()override;			//����������

	unsigned int color;					//�p�[�e�B�N���̐F

	//�萔
	const float MAX_POP_TIME;		//�p�[�e�B�N���̍ő�o������
	const float POSITION_Y;			//�p�[�e�B�N����Y���W
};