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

	VECTOR targetPosition;			//�ړI�n�̍��W
	float speed;					//�G�l�~�[�̈ړ����x
	float changeSpeed;				//�X�e�[�W���Ƃ̃G�l�~�[�̈ړ����x
	float length;					//����p�̋���
	float bulletDirection;			//�o���b�g�ƃG�l�~�[�̋���
	bool playerSpotted;				//�v���C���[�𔭌��������ǂ���
	bool cakeFlag;					//�P�[�L�𔭌��������ǂ���
	int markImage;					//�r�b�N���}�[�N�摜�i�[�p
	int cakeImage[2];				//�P�[�L�̉摜�i�[�p

	int visualModelHandle;			//���샂�f���n���h��
	VECTOR visualPosition;			//���샂�f���̈ʒu
	VECTOR visualDir;				//���샂�f���̕���



	//�萔
	const float RANGE_DEGREE;		//����p�x
	const int   CAKE_IMAGE_NUMBER;	//�P�[�L�摜��
	
};