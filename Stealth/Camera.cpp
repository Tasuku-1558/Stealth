#include "Camera.h"

const float  Camera::NEAR_DISTANCE = 1.0f;						//カメラに映る手前の範囲
const float  Camera::FAR_DISTANCE = 2000.0f;					//カメラに映る最奥の範囲
const VECTOR Camera::INITIAL_POSITION = { 0.0f, 1500.0f, 100.0f };	//初期位置
const VECTOR Camera::UP_VECTOR = { 0.0f, 700.0f, 10.0f };		//カメラの上方向

Camera::Camera()
{
	//処理なし
}

Camera::~Camera()
{
	//処理なし
}

void Camera::Initialize()
{
	//カメラの手前と奥野距離を設定
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);

    SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
    
}

void Camera::Update()
{
   
}

void Camera::Draw()
{
   
}