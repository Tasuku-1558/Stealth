#include "Camera.h"
#include "Player.h"
#include <math.h>

using namespace Math3d;

const float  Camera::NEAR_DISTANCE	  = 1.0f;						//�J�����ɉf���O�͈̔�
const float  Camera::FAR_DISTANCE	  = 2000.0f;					//�J�����ɉf��ŉ��͈̔�
const VECTOR Camera::INITIAL_POSITION = { 0.0f, 1500.0f, -100.0f };	//�����ʒu
const VECTOR Camera::UP_VECTOR		  = { 0.0f, /*1200.0f*/0.0f, 0.0f };	//�J�����̒����_

Camera::Camera()
	: position()
	, radius(580.0f)
	, yaw(0.0f)
{
	//�����Ȃ�
}

Camera::~Camera()
{
	//�����Ȃ�
}

void Camera::Initialize()
{
	//�J�����̎�O�Ɖ��̋�����ݒ�
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);
	
	//SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}

void Camera::Activate()
{
}

void Camera::Update(Player* player)
{
	position.x = radius * cos(yaw) + player->GetPosition().x;
	position.y = 1500.0f;
	position.z = radius * sin(yaw) + player->GetPosition().z;

	SetCameraPositionAndTarget_UpVecY(position, player->GetPosition());
	
	VECTOR front = player->GetPosition() - position;
	front.y = 0.0f;

	front = VNorm(front);

	VECTOR yaxis = { 0,1,0 };

	player->GetUp() = front;
	player->GetDown() = VScale(front, -1.0f);
	player->GetRight() = VCross(yaxis, front);
	player->GetLeft() = VScale(player->GetRight(), -1.0f);
	
	
}