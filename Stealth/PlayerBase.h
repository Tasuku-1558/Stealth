#pragma once

#include <string>

#include "ObjectBase.h"


/// <summary>
/// Playerの親クラス
/// ObjectBaseクラスを継承
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	 virtual ~PlayerBase();

protected:

	VECTOR inputDirection;			//入力された方向
	bool   inputFlag;				//キー入力フラグ
	float  speed;					//移動速度
	VECTOR previewPosition;			//未来のプレイヤーの位置
	int	   playerFindCount;			//エネミーに見つかった回数を数える
	int	   spottedSe;				//エネミーに見つかった時のSE音格納用
	bool   spottedSeFlag;			//エネミーに見つかった時のSE音を流すか流さないか


	//静的定数
	static const float  SPEED;		//移動速度
	static const VECTOR POSITION;	//モデルの位置
	static const VECTOR DIR;		//モデルの向き

	//static const VECTOR UP;		//上方向
	//static const VECTOR DOWN;		//下方向
	//static const VECTOR LEFT;		//左方向
	//static const VECTOR RIGHT;	//右方向
};