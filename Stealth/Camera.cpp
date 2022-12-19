#include "Camera.h"
#include "Player.h"
#include <math.h>

using namespace Math3d;

const float  Camera::NEAR_DISTANCE	   = 1.0f;								//�J�����ɉf���O�͈̔�
const float  Camera::FAR_DISTANCE	   = 5000.0f;							//�J�����ɉf��ŉ��͈̔�
const float  Camera::ROTATING_VELOCITY = 0.02f;								//�J�����̉�]���x
const VECTOR Camera::INITIAL_POSITION  = { 0.0f, 3000.0f, -100.0f };		//�����ʒu
const VECTOR Camera::UP_VECTOR		   = { 0.0f, 0.0f, 0.0f };	//�J�����̒����_

Camera::Camera()
	: position()
	, radius(200.0f)
	, yaw(0.0f)
	, front()
	, Up()
	, Down()
	, Right()
	, Left()
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

void Camera::Update(Player* player)
{
	//Q�L�[�ō���]
	if (CheckHitKey(KEY_INPUT_Q)) { yaw += ROTATING_VELOCITY; }

	//E�L�[�ŉE��]
	if (CheckHitKey(KEY_INPUT_E)) { yaw -= ROTATING_VELOCITY; }

	position = VGet(radius * cos(yaw) + player->GetPosition().x, 
					3000.0f, 
					radius * sin(yaw) + player->GetPosition().z);

	SetCameraPositionAndTarget_UpVecY(position, player->GetPosition());
	
	//�J�����̐��ʕ����̃x�N�g�����v�Z
	front = player->GetPosition() - position;
	front.y = 0.0f;

	//�x�N�g���𐳋K��
	front = VNorm(front);

	VECTOR yaxis = { 0,1,0 };

	/*player->GetUp() = front;
	player->GetDown() = VScale(front, -1.0f);
	player->GetRight() = VCross(yaxis, front);
	player->GetLeft() = VScale(player->GetRight(), -1.0f);*/

	Up	  = front;
	Down  = VScale(front, -1.0f);
	Right = VCross(yaxis, front);
	Left  = VScale(Right, -1.0f);
}