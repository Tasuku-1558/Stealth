#pragma once

#include <string>
#include <vector>
#include "ObjectBase.h"

using namespace std;

/// <summary>
/// エネミー基底クラス
/// </summary>
class EnemyBase : public ObjectBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

protected:

	vector<VECTOR>& GetList(int number) { return positionList[number]; }      //敵の行動パターンリストを返す

	int markImage;					//ビックリマーク画像格納用
	int visualModelHandle;			//視野モデルハンドル
	float speed;					//エネミーの移動速度
	float changeSpeed;				//ステージごとのエネミーの移動速度
	float playerDirection;			//プレイヤーとエネミーの距離
	float bulletDirection;			//バレットとエネミーの距離
	float rotateTime;				//回転時間
	bool playerSpotted;				//プレイヤーを発見したかどうか
	bool cakeFlag;					//ケーキを発見したかどうか
	VECTOR targetPosition;			//目的地の座標
	VECTOR visualPosition;			//視野モデルの位置
	VECTOR visualDir;				//視野モデルの方向


	//定数
	const int	 ROTATE_TIME_CATEGORY;	//回転時間の種類
	const float  RANGE_DEGREE;			//視野角度
	const float  LENGTH;				//視野角の距離
	const float  TARGET_ANGLE;			//回転の目標角度
	const float  INITIAL_ROTATE_TIME;	//初期の回転時間
	const float  RADIUS;				//エネミーの半径
	const float	 Y_ANGLE;				//Y軸の回転値
	const float  Y_ANGLE_SPEED;			//Y軸回転スピード
	const float  NOMAL_ROTATE_TIME;		//通常の回転時間
	const float  PLAYER_ROTATE_TIME;	//プレイヤーだった時の回転時間
	const float  CAKE_ROTATE_TIME;		//ケーキだった時の回転時間
	const float  STOP_SPEED;			//エネミーの移動速度を停止させる
	const string IMAGE_FOLDER_PATH;		//Imageフォルダまでのパス
	const string MARK_PATH;				//ビックリマーク画像のパス
	
private:
	EnemyBase(const EnemyBase&);		//コピーコンストラクタ

	//FirstStageでの敵の行動
	void MapList();                     //敵の行動パターンリスト(左右移動の敵)

	//SecondStageでの敵の行動
	void MapList2();                    //敵の行動パターンリスト2(壁の周りを回る敵)
	void MapList3();                    //敵の行動パターンリスト3(上下移動の敵)

	vector<VECTOR> positionList[9];
	vector<VECTOR>::iterator itr[9];

};