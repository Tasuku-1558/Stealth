#pragma once

#include "DxLib.h"
#include "Math3D.h"


/// <summary>
/// カメラクラス(固定型カメラ)
/// </summary>
class Camera final
{
public:
	 Camera();
	 virtual ~Camera();

	void Initialize();						//初期化処理
	void Update(VECTOR pos);				//更新処理

	VECTOR GetUp()	  { return up; }
	VECTOR GetDown()  { return down; }
	VECTOR GetRight() { return right; }
	VECTOR GetLeft()  { return left; }
	
private:

	VECTOR position;		//カメラの位置
	VECTOR front;
	const float radius;		//カメラ回転半径
	float yaw;				//カメラ回転角
	float angleY;
	
	VECTOR up;				//上方向
	VECTOR down;			//下方向
	VECTOR right;			//右方向
	VECTOR left;			//左方向

	//静的定数
	static const float  NEAR_DISTANCE;		//カメラに映る手前の範囲
	static const float  FAR_DISTANCE;		//カメラに映る最奥の範囲
	//static const VECTOR INITIAL_POSITION;	//初期位置
	//static const VECTOR UP_VECTOR;		//カメラの上方向
};

