#pragma once

#include "ObjectBase.h"


/// <summary>
/// Enemy�̐e�N���X
/// ObjectBase�N���X���p��
/// </summary>
class EnemyBase : public ObjectBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

protected:

	Object object;					//�I�u�W�F�N�g�̃^�O

	VECTOR targetPosition;			//�ړI�n�̍��W

	float speed;					//�G�l�~�[�̈ړ����x
	float length;					//����p�̋���

	bool playerSpotted;				//�v���C���[�𔭌��������ǂ���
	bool ballFlag;					//�{�[���𔭌��������ǂ���
	int playerFindCount;			//�v���C���[����������

	int findImage;					//���������摜�i�[�p
	int markImage;					//�r�b�N���}�[�N�摜�i�[�p
	int spottedSE;					//�v���C���[����SE��

	int visualModelHandle;			//���샂�f���n���h��
	VECTOR visualPosition;			//���샂�f���̈ʒu
	VECTOR visualDir;				//���샂�f���̕���



	//�ÓI�萔
	static const float SPEED;				//�ړ����x
	static const float RANGE_DEGREE;		//����p�x
	
};