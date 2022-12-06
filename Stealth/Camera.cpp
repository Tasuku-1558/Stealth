#include "Camera.h"

const float  Camera::NEAR_DISTANCE = 1.0f;						//�J�����ɉf���O�͈̔�
const float  Camera::FAR_DISTANCE = 2000.0f;					//�J�����ɉf��ŉ��͈̔�
const VECTOR Camera::INITIAL_POSITION = { 0.0f, 1500.0f, 100.0f };	//�����ʒu
const VECTOR Camera::UP_VECTOR = { 0.0f, 700.0f, 10.0f };		//�J�����̏����

Camera::Camera()
{
	//�����Ȃ�
}

Camera::~Camera()
{
	//�����Ȃ�
}

void Camera::Initialize()
{
	//�J�����̎�O�Ɖ��싗����ݒ�
	SetCameraNearFar(NEAR_DISTANCE, FAR_DISTANCE);

    SetCameraPositionAndTarget_UpVecY(INITIAL_POSITION, UP_VECTOR);
    
}

void Camera::Update()
{
   
}

void Camera::Draw()
{
   
}