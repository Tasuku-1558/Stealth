#pragma once

#include "ParticleBase.h"


/// <summary>
/// �P�[�L�p�[�e�B�N���N���X
/// �P�[�L���ˎ��ɏo���p�[�e�B�N��
/// </summary>
class CakeParticle final : public ParticleBase
{
public:
	CakeParticle(const VECTOR& particlePosition);
	virtual ~CakeParticle();

	void Update(float deltaTime)override;	//�X�V����
	void Draw()override;					//�`�揈��

private:
	CakeParticle(const CakeParticle&);	//�R�s�[�R���X�g���N�^

	void Initialize()override;				//����������

	float particlePopTime;				//�p�[�e�B�N���̏o������

	//�萔
	const unsigned int PINK;			//�p�[�e�B�N���̃J���[
	const float POS_Y;					//�p�[�e�B�N����Y���W
};