#include "Camera.h"
#include <math.h>

using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
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
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Camera::Initialize()
{
	//�J�����̎�O�Ɖ��̋�����ݒ�
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="playerPos"></param>
void Camera::Update(VECTOR playerPos)
{
	//�J�����̎��_��ݒ�
	position = VGet(radius * cosf(yaw) + playerPos.x,
					angleY,
					radius * sinf(yaw) + playerPos.z);

	//�J�����̎��_�A�����_��ݒ�
	SetCameraPositionAndTarget_UpVecY(position, playerPos);


	//�J�����̐��ʕ����̃x�N�g�����v�Z
	front = playerPos - position;
	front.y = 0.0f;

	//�x�N�g���𐳋K��
	front = VNorm(front);

	VECTOR yaxis = { 0,1,0 };

	up	  = front;
	down  = VScale(front, -1.0f);
	right = VCross(yaxis, front);
	left  = VScale(right, -1.0f);
}

/// <summary>
/// �X�e�[�W�Z���N�V������ʂƃ��U���g��ʂ̃J����
/// </summary>
void Camera::SelectionAndResultCamera()
{
	//�J�����̎��_�A�����_��ݒ�
	SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}