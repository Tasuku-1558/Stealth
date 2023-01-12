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

	float speed;
	const float length;				//����p�̋���
	bool discovery;					//����

	int playerFindCount;			//�v���C���[����������

	int findImage;					//���������摜�i�[�p
	int viewRangeImage;
	int markImage;					//�r�b�N���}�[�N�摜�i�[�p
	int discoverySE;				//�v���C���[����SE��
	bool ballFlag;
	int count;

	//�ÓI�萔
	static const float SPEED;				//�ړ����x
	static const float RANGE_DEGREE;		//����p�x
	
};