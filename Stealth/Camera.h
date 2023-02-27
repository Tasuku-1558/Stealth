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

	void Initialize();							//初期化処理
	void Update(VECTOR playerPos);				//更新処理
	void SelectionAndResultCamera();			//ステージセレクション画面とリザルト画面のカメラ

	const VECTOR GetUp()	{ return up; }		//カメラの上方向を返す
	const VECTOR GetDown()  { return down; }	//カメラの下方向を返す
	const VECTOR GetRight() { return right; }	//カメラの右方向を返す
	const VECTOR GetLeft()  { return left; }	//カメラの左方向を返す
	
private:

	VECTOR position;		//カメラの位置
	VECTOR front;
	const float radius;		//カメラ回転半径
	float yaw;				//カメラ回転角
	float angleY;
	
	VECTOR up;				//カメラの上方向
	VECTOR down;			//カメラの下方向
	VECTOR right;			//カメラの右方向
	VECTOR left;			//カメラの左方向

	//定数
	const float  NEAR_DISTANCE;		//カメラに映る手前の範囲
	const float  FAR_DISTANCE;		//カメラに映る最奥の範囲
	const VECTOR INITIAL_POSITION;	//初期位置
	const VECTOR UP_VECTOR;			//カメラの上方向
};

