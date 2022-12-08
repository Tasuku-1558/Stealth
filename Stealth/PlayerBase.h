#pragma once

#include "ObjectBase.h"

//Player�̐e�N���X
//ObjectBase���p��

class PlayerBase : public ObjectBase
{
public:
			  PlayerBase();
	 virtual ~PlayerBase();

protected:
	VECTOR inputDirection;			//���͂��ꂽ����
	bool   inputFlag;				//�L�[���̓t���O
	int	   hp;						//�v���C���[��HP

	//�ÓI�萔
	static const float SPEED;			//�ړ����x
	static const VECTOR POSITION;		//���f���̈ʒu
	static const VECTOR DIR;			//���f���̌���
	static const int	HP;				//�v���C���[��HP
};