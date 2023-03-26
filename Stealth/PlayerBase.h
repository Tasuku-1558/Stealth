#pragma once

#include "ObjectBase.h"
#include <string>


/// <summary>
/// プレイヤー基底クラス
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

protected:

	VECTOR inputDirection;		//入力された方向
	VECTOR nextPosition;		//未来のプレイヤーの位置
	int	   playerFindCount;		//エネミーに見つかった回数を数える
	int	   playerFindImage;		//エネミーに見つかった画像格納用
	int	   findImageX;			//見つかった画像のX座標
	int    findImageY;			//見つかった画像のY座標
	float  speed;				//移動速度
	float  initialTime;			//プレイヤーの情報を初期化する時間
	bool   inputFlag;			//キー入力フラグ
	bool   findImageFlag;		//エネミーに見つかった画像を表示するかしないか
	bool   spottedSeFlag;		//エネミーに見つかった時のSE音を流すか流さないか


	//定数
	const float	  SPEED;						//移動速度
	const float	  OPACITY;						//不透明度
	const float	  RADIUS;						//プレイヤーの半径
	const VECTOR  POSITION;						//モデルの位置
	const VECTOR  DIRECTION;					//モデルの向き
	const VECTOR  UP;							//上方向
	const VECTOR  DOWN;							//下方向
	const VECTOR  LEFT;							//左方向
	const VECTOR  RIGHT;						//右方向
	const VECTOR  AFTER_IMAGE_ADJUSTMENT;		//残像の調整値
	const COLOR_F AFTER_IMAGE_COLOR;			//残像モデルのエミッシブカラー
};