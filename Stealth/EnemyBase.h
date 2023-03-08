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

	VECTOR targetPosition;			//目的地の座標
	VECTOR visualPosition;			//視野モデルの位置
	VECTOR visualDir;				//視野モデルの方向
	int markImage;					//ビックリマーク画像格納用
	int cakeImage[2];				//ケーキの画像格納用
	int visualModelHandle;			//視野モデルハンドル
	float speed;					//エネミーの移動速度
	float changeSpeed;				//ステージごとのエネミーの移動速度
	float length;					//視野角の距離
	float bulletDirection;			//バレットとエネミーの距離
	bool playerSpotted;				//プレイヤーを発見したかどうか
	bool cakeFlag;					//ケーキを発見したかどうか


	//定数
	const float RANGE_DEGREE;		//視野角度
	const float RADIUS;				//エネミーの半径
	const int   CAKE_IMAGE_NUMBER;	//ケーキ画像数
	
};