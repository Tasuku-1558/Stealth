#include "Camera.h"
#include <math.h>

using namespace Math3d;

const float  Camera::NEAR_DISTANCE	   = 1.0f;								//カメラに映る手前の範囲
const float  Camera::FAR_DISTANCE	   = 4000.0f;							//カメラに映る最奥の範囲
//const VECTOR Camera::INITIAL_POSITION  = { 0.0f, 2000.0f, -100.0f };		//初期位置
//const VECTOR Camera::UP_VECTOR		 = { 0.0f, 0.0f, 0.0f };			//カメラの注視点

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
/// <param name="pos"></param>
void Camera::Update(VECTOR pos)
{
	if (CheckHitKey(KEY_INPUT_V))
	{
		angleY += 100.0f;
	}
	if (CheckHitKey(KEY_INPUT_B))
	{
		angleY -= 100.0f;
	}

	//カメラの視点を設定
	position = VGet(radius * cosf(yaw) + pos.x,
					angleY,
					radius * sinf(yaw) + pos.z);

	//カメラの視点、注視点を設定
	SetCameraPositionAndTarget_UpVecY(position, pos);


	//カメラの正面方向のベクトルを計算
	front = pos - position;
	front.y = 0.0f;

	//ベクトルを正規化
	front = VNorm(front);

	VECTOR yaxis = { 0,1,0 };

	up	  = front;
	down  = VScale(front, -1.0f);
	right = VCross(yaxis, front);
	left  = VScale(right, -1.0f);
}