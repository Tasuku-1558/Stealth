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

	float speed;

	//�ÓI�萔
	static const float SPEED;				//�ړ����x
	static const float RANGE_DEGREE;		//����p�x
	
};