#include "Camera.h"
#include "Player.h"
#include <math.h>

using namespace Math3d;

const float  Camera::NEAR_DISTANCE	   = 1.0f;								//カメラに映る手前の範囲
const float  Camera::FAR_DISTANCE	   = 3000.0f;							//カメラに映る最奥の範囲
const float  Camera::ROTATING_VELOCITY = 0.02f;								//カメラの回転速度
const VECTOR Camera::INITIAL_POSITION  = { 0.0f, 2000.0f, -100.0f };		//初期位置
const VECTOR Camera::UP_VECTOR		   = { 0.0f, /*1200.0f*/0.0f, 0.0f };	//カメラの注視点

Camera::Camera()
	: position()
	, radius(300.0f)
	, yaw(0.0f)
	, front()
{
	//処理なし
}

Camera::~Camera()
{
	//処理なし
}

void Camera::Initialize()
{
	//カメラの手前と奥の距離を設定
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);
	
	//SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}

void Camera::Activate()
{
}

void Camera::Update(Player* player)
{
	//Qキーで左回転
	if (CheckHitKey(KEY_INPUT_Q)) { yaw += ROTATING_VELOCITY; }

	//Eキーで右回転
	if (CheckHitKey(KEY_INPUT_E)) { yaw -= ROTATING_VELOCITY; }


	position.x = radius * cos(yaw) + player->GetPosition().x;
	position.y = 2000.0f;
	position.z = radius * sin(yaw) + player->GetPosition().z;

	SetCameraPositionAndTarget_UpVecY(position, player->GetPosition());
	
	front = player->GetPosition() - position;
	front.y = 0.0f;

	front = VNorm(front);

	VECTOR yaxis = { 0,1,0 };

	player->GetUp() = front;
	player->GetDown() = VScale(front, -1.0f);
	player->GetRight() = VCross(yaxis, front);
	player->GetLeft() = VScale(player->GetRight(), -1.0f);
	
}