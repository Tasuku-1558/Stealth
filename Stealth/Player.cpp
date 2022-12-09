#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

const VECTOR Player::RIGHT_ARM_POSITION = { 150.0f, 0.0f, 110.0f };

//�R���X�g���N�^
Player::Player() : PlayerBase()
	, rightArmHandle(0)
	, rightArmPosition()
{
	playerState = PlayerState::Nomal;
}

//�f�X�g���N�^
Player::~Player()
{
	//�I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL || rightArmHandle != NULL)
	{
		Finalize();
	}
}

//����������
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_BODY));
	

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s[PLAYER_BODY]\n");
	}

	rightArmHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_ARM));

	//�ǂݍ��ݎ��s�ŃG���[
	if (rightArmHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s[PLAYER_ARM]\n");
	}
}

//�I������
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(rightArmHandle);
	rightArmHandle = NULL;
}

//����������
void Player::Activate()
{
	position = POSITION;
	rightArmPosition = RIGHT_ARM_POSITION;

	dir = { 0.0f,0.0f,1.0f };

	hp = HP;
}

//�X�V����
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	//�v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);


	MV1SetPosition(rightArmHandle, rightArmPosition);
}

//�ړ�����
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	//�㉺
	if (CheckHitKey(KEY_INPUT_UP))
	{
		inputDirection += UP;
		inputFlag = true;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		inputDirection += DOWN;
		inputFlag = true;
	}
	//���E
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		inputDirection += RIGHT;
		inputFlag = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		inputDirection += LEFT;
		inputFlag = true;
	}

	//�\���L�[�̓��͂���������
	if (inputFlag)
	{
		//�\���L�[�̓��͕����𐳋K��
		inputDirection = VNorm(inputDirection);

		//�\���L�[�̓��͕������L�����̌����Ƃ���
		dir = inputDirection;

		//�\���L�[�̈ړ������Ɉړ�
		position += inputDirection * SPEED * deltaTime;

		rightArmPosition += inputDirection * SPEED * deltaTime;

	}

	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g dir������
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	MV1SetRotationZYAxis(rightArmHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
}

void Player::pUpdate()
{
	switch (playerState)
	{
	case PlayerState::Nomal:
		break;

	case PlayerState::Damage:
		break;
	}
}

//�`�揈��
void Player::Draw()
{
	pUpdate();

	MV1DrawModel(modelHandle);

	MV1DrawModel(rightArmHandle);
}