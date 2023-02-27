#pragma once

#include "ObjectBase.h"
#include <string>


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
	int	   playerFindImage;			//エネミーに見つかった画像格納用
	bool   findImageFlag;			//エネミーに見つかった画像を表示するかしないか
	bool   spottedSeFlag;			//エネミーに見つかった時のSE音を流すか流さないか


	//定数
	const float  SPEED;		//移動速度
	const VECTOR POSITION;	//モデルの位置
	const VECTOR DIR;		//モデルの向き

	//const VECTOR UP;		//上方向
	//const VECTOR DOWN;	//下方向
	//const VECTOR LEFT;	//左方向
	//const VECTOR RIGHT;	//右方向
};