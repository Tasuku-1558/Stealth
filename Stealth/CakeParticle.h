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
	void DeleteParticle()override;			//�폜����

private:
	CakeParticle(const CakeParticle&);	//�R�s�[�R���X�g���N�^

	void Initialize()override;			//����������


	//�萔
	const unsigned int PINK;		//�p�[�e�B�N���̃J���[
	const float MAX_POP_TIME;		//�p�[�e�B�N���̍ő�o������
	const float POSITION_Y;			//�p�[�e�B�N����Y���W
};