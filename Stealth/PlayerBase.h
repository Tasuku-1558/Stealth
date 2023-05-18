#pragma once

#include <string>
#include "ObjectBase.h"

using namespace std;

/// <summary>
/// プレイヤー基底クラス
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

protected:

	int	   playerFindCount;		//エネミーに見つかった回数を数える
	int	   playerFindImage;		//エネミーに見つかった画像格納用
	int	   afterImageModel[12];	//残像モデル格納用
	float  speed;				//移動速度
	float  initialTime;			//初期位置に戻すカウント
	bool   inputFlag;			//キー入力フラグ
	bool   findImageFlag;		//エネミーに見つかった画像を表示するかしないか
	bool   spottedSeFlag;		//エネミーに見つかった時のSE音を流すか流さないか
	VECTOR inputDirection;		//入力された方向
	VECTOR nextPosition;		//未来のプレイヤーの位置
	VECTOR pastPosition[12];	//プレイヤーの過去の位置

	//定数
	const int	  FIND_IMAGE_X;				//見つかった画像のX座標
	const int	  FIND_IMAGE_Y;				//見つかった画像のY座標
	const int	  AFTER_IMAGE_NUMBER;		//プレイヤーの残像枚数
	const int	  MATERIAL_INDEX;			//エミッシブカラーを変更するマテリアルの番号
	const int	  KEY_INPUT_PATTERN;		//キー入力パターン

	const float	  INITIAL_SPEED;			//初期の移動速度
	const float	  OPACITY;					//不透明度
	const float	  RADIUS;					//半径
	const float	  Y_ANGLE;					//Y軸の回転値
	const float   MAX_INITIAL_TIME;			//初期位置に戻す最大カウント
	const float	  INITIAL_TIME;				//初期位置に戻すカウント
	const float   STOP_SPEED;				//プレイヤーの移動速度を停止させる
	const float	  MAX_INPUT_DIRECTION;		//最大の入力された方向

	const VECTOR  INITIAL_POSITION;			//初期のプレイヤーの位置
	const VECTOR  INITIAL_DIRECTION;		//初期のプレイヤーの向き
	const VECTOR  UP;						//上方向
	const VECTOR  DOWN;						//下方向
	const VECTOR  LEFT;						//左方向
	const VECTOR  RIGHT;					//右方向
	const VECTOR  AFTER_IMAGE_ADJUSTMENT;	//残像の調整値

	const string  IMAGE_FOLDER_PATH;		//Imageフォルダまでのパス
	const string  PLAYER_FIND_PATH;			//エネミーに見つかった時の画像のパス

	const COLOR_F AFTER_IMAGE_COLOR;		//残像モデルのエミッシブカラー

private:
	PlayerBase(const PlayerBase&);			//コピーコンストラクタ
};