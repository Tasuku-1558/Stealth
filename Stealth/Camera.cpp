#include "Camera.h"
#include <math.h>

using namespace Math3d;

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
	: position()
	, radius(400.0f)
	, yaw(0.0f)
	, front()
	, up()
	, down()
	, right()
	, left()
	, angleY(2500.0f)
	, NEAR_DISTANCE(1.0f)
	, FAR_DISTANCE(4000.0f)
	, INITIAL_POSITION({ 0.0f, 2000.0f, -100.0f })
	, UP_VECTOR({ 0.0f, 0.0f, 0.0f })
{
	//処理なし
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
	//カメラの視点を設定
	position = VGet(radius * cosf(yaw) + playerPos.x,
					angleY,
					radius * sinf(yaw) + playerPos.z);

	//カメラの視点、注視点を設定
	SetCameraPositionAndTarget_UpVecY(position, playerPos);


	//カメラの正面方向のベクトルを計算
	front = playerPos - position;
	front.y = 0.0f;

	//ベクトルを正規化
	front = VNorm(front);

	VECTOR yaxis = { 0,1,0 };

	up	  = front;
	down  = VScale(front, -1.0f);
	right = VCross(yaxis, front);
	left  = VScale(right, -1.0f);
}

/// <summary>
/// ステージセレクション画面とリザルト画面のカメラ
/// </summary>
void Camera::SelectionAndResultCamera()
{
	//カメラの視点、注視点を設定
	SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}