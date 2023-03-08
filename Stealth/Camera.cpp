#include "Camera.h"

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
	: position()
	, lookPos()
	, aimCameraPos()
	, lookMoveDir()
	, aimLookPos()
	, posMoveDir()
	, cameraOffset({ 0.0f, 2500.0f, -500.0f })
	, NEAR_DISTANCE(1.0f)
	, FAR_DISTANCE(4000.0f)
	, INITIAL_POSITION({ 0.0f, 2000.0f, -100.0f })
	, UP_VECTOR({ 0.0f, 0.0f, 0.0f })
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Camera::Initialize()
{
	//カメラの手前と奥の距離を設定
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="playerPos"></param>
void Camera::Update(VECTOR playerPos)
{
	//プレイヤーの位置を保存
	aimLookPos = playerPos;

	aimCameraPos = aimLookPos + cameraOffset;

	lookMoveDir = aimLookPos - lookPos;
	posMoveDir = aimCameraPos - position;

	position += posMoveDir;
	lookPos += lookMoveDir;

	//カメラの視点、注視点を設定
	SetCameraPositionAndTarget_UpVecY(position, lookPos);
}

/// <summary>
/// ステージセレクション画面とリザルト画面のカメラ
/// </summary>
void Camera::SelectionAndResultCamera()
{
	//カメラの視点、注視点を設定
	SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}