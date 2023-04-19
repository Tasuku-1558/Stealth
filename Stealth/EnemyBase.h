#pragma once

#include "ObjectBase.h"
#include <vector>

/// <summary>
/// エネミー基底クラス
/// </summary>
class EnemyBase : public ObjectBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

protected:

	std::vector<VECTOR>& GetList(int number) { return positionList[number]; }      //敵の行動パターンリストを返す

	int markImage;					//ビックリマーク画像格納用
	int visualModelHandle;			//視野モデルハンドル
	float speed;					//エネミーの移動速度
	float changeSpeed;				//ステージごとのエネミーの移動速度
	float length;					//視野角の距離
	float bulletDirection;			//バレットとエネミーの距離
	float rotateTime;				//回転時間
	bool playerSpotted;				//プレイヤーを発見したかどうか
	bool cakeFlag;					//ケーキを発見したかどうか
	VECTOR targetPosition;			//目的地の座標
	VECTOR visualPosition;			//視野モデルの位置
	VECTOR visualDir;				//視野モデルの方向


	//定数
	const float RANGE_DEGREE;			//視野角度
	const float TARGET_ANGLE;			//回転の目標角度
	const float INITIAL_ROTATE_TIME;	//初期の回転時間
	const float RADIUS;					//エネミーの半径
	const float STOP_SPEED;				//エネミーの移動速度を停止させる
	
private:

	//FirstStageでの敵の行動
	void MapList();                         //敵の行動パターンリスト(左右移動の敵)

	//SecondStageでの敵の行動
	void MapList2();                        //敵の行動パターンリスト2(壁の周りを回る敵)
	void MapList3();                        //敵の行動パターンリスト3(上下移動の敵)


	std::vector<VECTOR> positionList[9];
	std::vector<VECTOR>::iterator itr[9];

};