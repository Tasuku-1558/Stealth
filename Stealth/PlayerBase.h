#pragma once

#include "ObjectBase.h"
#include <string>


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
	int	   playerFindImage;			//�G�l�~�[�Ɍ��������摜�i�[�p
	bool   findImageFlag;			//�G�l�~�[�Ɍ��������摜��\�����邩���Ȃ���
	bool   spottedSeFlag;			//�G�l�~�[�Ɍ�����������SE���𗬂��������Ȃ���


	//�萔
	const float  SPEED;		//�ړ����x
	const VECTOR POSITION;	//���f���̈ʒu
	const VECTOR DIR;		//���f���̌���

	//const VECTOR UP;		//�����
	//const VECTOR DOWN;	//������
	//const VECTOR LEFT;	//������
	//const VECTOR RIGHT;	//�E����
};