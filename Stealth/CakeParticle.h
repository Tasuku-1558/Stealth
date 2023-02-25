#pragma once

#include "DxLib.h"
#include "ParticleBase.h"


/// <summary>
/// �P�[�L�p�[�e�B�N���N���X
/// �P�[�L���ˎ��ɏo���p�[�e�B�N��
/// </summary>
class CakeParticle final : public ParticleBase
{
public:
	CakeParticle(const VECTOR& pos);
	virtual ~CakeParticle();

	void Initialize();				//����������
	void Activate();				//����������
	void Update(float deltaTime);	//�X�V����
	void Draw();					//�`�揈��

private:
	CakeParticle(const CakeParticle&);	//�R�s�[�R���X�g���N�^

	//�萔
	const unsigned int PINK;		//�p�[�e�B�N���̃J���[
};