#pragma once

#include "DxLib.h"

/// <summary>
/// �p�[�e�B�N���x�[�X�N���X
/// </summary>
class ParticleBase
{
public:

	ParticleBase();
	virtual ~ParticleBase();

	virtual void Initialize() = 0;				//����������
	virtual void Activate() = 0;				//����������
	virtual void Update(float deltaTime) = 0;	//�X�V����
	virtual void Draw() = 0;					//�`�揈��

	const bool IsParticleEnd() { return endFlag; }		//�p�[�e�B�N���������t���O��Ԃ�

protected:

	VECTOR position;		//�p�[�e�B�N���̈ʒu
	float radius;			//�p�[�e�B�N���̔��a
	float particleCount;	//�p�[�e�B�N���J�E���g
	float particlePopTime;	//�p�[�e�B�N���̏o������
	bool endFlag;			//�p�[�e�B�N���������������Ȃ���
	float xPower;			//�������̗�
	float zPower;			//�c�����̗�
};