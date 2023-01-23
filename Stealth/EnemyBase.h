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

	Object object;					//オブジェクトのタグ

	VECTOR targetPosition;			//目的地の座標

	float speed;					//エネミーの移動速度
	const float length;				//視野角の距離

	bool discovery;					//プレイヤーを発見したかどうか
	int playerFindCount;			//プレイヤーを見つけた回数

	int findImage;					//見つかった画像格納用
	int markImage;					//ビックリマーク画像格納用
	int discoverySE;				//プレイヤー発見SE音

	int visualModelHandle;			//視野モデルハンドル
	VECTOR visualPosition;			//視野モデルの位置
	VECTOR visualDir;				//視野モデルの方向



	//静的定数
	static const float SPEED;				//移動速度
	static const float RANGE_DEGREE;		//視野角度
	
};