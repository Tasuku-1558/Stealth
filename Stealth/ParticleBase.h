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

	float  radius;				//���a
	float  particlePopCount;	//�p�[�e�B�N���o���J�E���g
	float  xPower;				//�������̗�
	float  zPower;				//�c�����̗�
	bool   endFlag;				//�����������Ȃ���
	VECTOR position;			//�ʒu

	//�萔
	const int DIVNUM;		//�|���S���ׂ̍���
	const int ALPHA;		//�A���t�@�u�����h
	const int NOBLEND;		//�f�t�H���g�u�����h����
};