#pragma once

#include "DxLib.h"

/// <summary>
/// �ԉ΃p�[�e�B�N���N���X
/// ���U���g��ʂŏo���p�[�e�B�N��
/// </summary>
class FireWorksParticle final
{
public:
	FireWorksParticle(const VECTOR& pos);
	virtual ~FireWorksParticle();

	void Initialize();				//����������
	void Activate();				//����������
	void Update(float deltaTime);	//�X�V����
	void Draw();					//�`�揈��

	const bool IsParticleEnd() { return endFlag; }		//�p�[�e�B�N���������t���O��Ԃ�

private:
	FireWorksParticle(const FireWorksParticle&);	//�R�s�[�R���X�g���N�^

	VECTOR position;		//�p�[�e�B�N���̈ʒu
	float radius;			//�p�[�e�B�N���̔��a
	float particleCount;	//�p�[�e�B�N���J�E���g
	float particlePopTime;	//�p�[�e�B�N���̏o������
	bool endFlag;			//�p�[�e�B�N��������
	float xPower;			//�������̗�
	float yPower;			//�c�����̗�


	//�ÓI�萔
	static const unsigned int ORANGE;		//�p�[�e�B�N���̃J���[
};