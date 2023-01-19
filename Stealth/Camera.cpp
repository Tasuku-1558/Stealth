#include "Camera.h"
#include <math.h>

using namespace Math3d;

const float  Camera::NEAR_DISTANCE	   = 1.0f;								//�J�����ɉf���O�͈̔�
const float  Camera::FAR_DISTANCE	   = 4000.0f;							//�J�����ɉf��ŉ��͈̔�
//const VECTOR Camera::INITIAL_POSITION  = { 0.0f, 2000.0f, -100.0f };		//�����ʒu
//const VECTOR Camera::UP_VECTOR		   = { 0.0f, 0.0f, 0.0f };				//�J�����̒����_

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
}

void Camera::Update(VECTOR pos)
{
	
	position = VGet(radius * cosf(yaw) + pos.x,
					angleY,
					radius * sinf(yaw) + pos.z);

	//�J�����̎��_�A�����_��ݒ�
	SetCameraPositionAndTarget_UpVecY(position, pos);


	//�J�����̐��ʕ����̃x�N�g�����v�Z
	front = pos - position;
	front.y = 0.0f;

	//�x�N�g���𐳋K��
	front = VNorm(front);

	VECTOR yaxis = { 0,1,0 };

	up	  = front;
	down  = VScale(front, -1.0f);
	right = VCross(yaxis, front);
	left  = VScale(right, -1.0f);
}