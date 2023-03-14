#pragma once

#include "DxLib.h"
#include "Math3D.h"


/// <summary>
/// カメラクラス
/// プレイヤーへの追従カメラ
/// </summary>
class Camera final
{
public:
	Camera();
	virtual ~Camera();

	void Update(VECTOR playerPosition);			//更新処理
	void SelectionAndResultCamera();			//ステージセレクション画面とリザルト画面のカメラ

private:
	Camera(const Camera&);						//コピーコンストラクタ

	void Initialize();							//初期化処理

	VECTOR position;		//カメラの位置
	VECTOR cameraOffset;	//プレイヤーからの相対位置
	VECTOR lookPos;			//カメラの注視点
	VECTOR aimLookPos;
	VECTOR aimCameraPos;
	VECTOR lookMoveDir;
	VECTOR posMoveDir;

	//定数
	const float  NEAR_DISTANCE;		//カメラに映る手前の範囲
	const float  FAR_DISTANCE;		//カメラに映る最奥の範囲
	const VECTOR INITIAL_POSITION;	//初期位置
	const VECTOR UP_VECTOR;			//カメラの上方向
};

