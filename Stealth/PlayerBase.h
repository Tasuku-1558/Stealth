#pragma once

#include <string>

#include "ObjectBase.h"


/// <summary>
/// Player�̐e�N���X
/// ObjectBase�N���X���p��
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	 virtual ~PlayerBase();

protected:

	VECTOR inputDirection;			//���͂��ꂽ����
	bool   inputFlag;				//�L�[���̓t���O
	float  speed;					//�ړ����x
	VECTOR previewPosition;			//�����̃v���C���[�̈ʒu
	int	   playerFindCount;			//�G�l�~�[�Ɍ��������񐔂𐔂���
	int	   spottedSe;				//�G�l�~�[�Ɍ�����������SE���i�[�p
	bool   spottedSeFlag;			//�G�l�~�[�Ɍ�����������SE���𗬂��������Ȃ���


	//�ÓI�萔
	static const float  SPEED;		//�ړ����x
	static const VECTOR POSITION;	//���f���̈ʒu
	static const VECTOR DIR;		//���f���̌���

	//static const VECTOR UP;		//�����
	//static const VECTOR DOWN;		//������
	//static const VECTOR LEFT;		//������
	//static const VECTOR RIGHT;	//�E����
};