#pragma once

#include "DxLib.h"

class Player;

/// <summary>
/// カメラクラス
/// </summary>
class Camera final
{
public:
	 Camera();	//コンストラクタ
	~Camera();	//デストラクタ

	void Initialize();
	void Update(Player* player);

	VECTOR GetUp()	  { return Up; }
	VECTOR GetDown()  { return Down; }
	VECTOR GetRight() { return Right; }
	VECTOR GetLeft()  { return Left; }
	
private:

	VECTOR position;		//カメラの位置
	VECTOR front;
	const float radius;		//カメラ回転半径
	float yaw;				//カメラ回転角
	
	VECTOR Up;				//上方向
	VECTOR Down;			//下方向
	VECTOR Right;			//右方向
	VECTOR Left;			//左方向

	//静的定数
	static const float  NEAR_DISTANCE;		//カメラに映る手前の範囲
	static const float  FAR_DISTANCE;		//カメラに映る最奥の範囲
	static const float  ROTATING_VELOCITY;	//カメラの回転速度
	static const VECTOR INITIAL_POSITION;	//初期位置
	static const VECTOR UP_VECTOR;			//カメラの上方向
};

