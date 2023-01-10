#pragma once

#include "ObjectBase.h"


/// <summary>
/// Enemyの親クラス
/// ObjectBaseクラスを継承
/// </summary>
class EnemyBase : public ObjectBase
{
public:
			 EnemyBase();
	virtual ~EnemyBase();

protected:

	float speed;

	//静的定数
	static const float SPEED;				//移動速度
	static const float RANGE_DEGREE;		//視野角度
	
};