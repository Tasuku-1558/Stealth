#pragma once

#include "DxLib.h"
#include "Math3D.h"
#include <math.h>

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �p�[�e�B�N�����N���X
/// </summary>
class ParticleBase
{
public:

	ParticleBase();
	virtual ~ParticleBase();

	virtual void Initialize() = 0;				//����������
	virtual void Update(float deltaTime) = 0;	//�X�V����
	virtual void Draw() = 0;					//�`�揈��

	const bool IsParticleEnd() { return endFlag; }		//�p�[�e�B�N���������t���O��Ԃ�

protected:

	VECTOR position;		//�p�[�e�B�N���̈ʒu
	float  radius;			//�p�[�e�B�N���̔��a
	float  particleCount;	//�p�[�e�B�N���J�E���g
	float  xPower;			//�������̗�
	float  zPower;			//�c�����̗�
	bool   endFlag;			//�p�[�e�B�N���������������Ȃ���

	//�萔
	const int DIVNUM;		//�p�[�e�B�N���̃|���S���ׂ̍���
};