#pragma once

#include "ObjectBase.h"


/// <summary>
/// Enemyの親クラス
/// ObjectBaseを継承
/// </summary>
class EnemyBase : public ObjectBase
{
public:
			 EnemyBase();
	virtual ~EnemyBase();

protected:

	//静的定数
	static const float SPEED;			//移動速度
	static const VECTOR POSITION;		//モデルの位置
	static const VECTOR DIR;			//モデルの向き
	
};