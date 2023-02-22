#pragma once

#include "DxLib.h"

/// <summary>
/// �P�[�L�p�[�e�B�N���N���X
/// �}�E�X�N���b�N���ɏo���p�[�e�B�N��
/// </summary>
class CakeParticle final
{
public:
	CakeParticle(const VECTOR& pos);
	virtual ~CakeParticle();

	void Initialize();				//����������
	void Activate();				//����������
	void Update(float deltaTime);	//�X�V����
	void Draw();					//�`�揈��

	const bool IsParticleEnd() { return endFlag; }		//�p�[�e�B�N���������t���O��Ԃ�

private:
	CakeParticle(const CakeParticle&);	//�R�s�[�R���X�g���N�^

	VECTOR position;		//�p�[�e�B�N���̈ʒu
	float radius;			//�p�[�e�B�N���̔��a
	float particleCount;	//�p�[�e�B�N���J�E���g
	float particlePopTime;	//�p�[�e�B�N���̏o������
	bool endFlag;			//�p�[�e�B�N���������������Ȃ���
	float xPower;			//�������̗�
	float zPower;			//�c�����̗�


	//�萔
	const unsigned int PINK;		//�p�[�e�B�N���̃J���[
};