#pragma once

#include "ObjectBase.h"

//Playerの親クラス
//ObjectBaseを継承

class PlayerBase : public ObjectBase
{
public:
			  PlayerBase();
	 virtual ~PlayerBase();

protected:
	VECTOR inputDirection;			//入力された方向
	bool   inputFlag;				//キー入力フラグ

	//静的定数
	static const float SPEED;			//移動速度
	static const VECTOR POSITION;		//モデルの位置
};