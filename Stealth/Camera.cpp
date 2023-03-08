#include "Camera.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
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
	//�v���C���[�̈ʒu��ۑ�
	aimLookPos = playerPos;

	aimCameraPos = aimLookPos + cameraOffset;

	lookMoveDir = aimLookPos - lookPos;
	posMoveDir = aimCameraPos - position;

	position += posMoveDir;
	lookPos += lookMoveDir;

	//�J�����̎��_�A�����_��ݒ�
	SetCameraPositionAndTarget_UpVecY(position, lookPos);
}

/// <summary>
/// �X�e�[�W�Z���N�V������ʂƃ��U���g��ʂ̃J����
/// </summary>
void Camera::SelectionAndResultCamera()
{
	//�J�����̎��_�A�����_��ݒ�
	SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
}