#pragma once

#include "ObjectBase.h"

//Enemy�̐e�N���X
//ObjectBase���p��

class EnemyBase : public ObjectBase
{
public:
			 EnemyBase();
	virtual ~EnemyBase();

protected:

	//�ÓI�萔
	static const float SPEED;			//�ړ����x
	static const VECTOR POSITION;		//���f���̈ʒu
	static const VECTOR DIR;			//���f���̌���

};