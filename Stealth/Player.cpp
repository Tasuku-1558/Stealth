#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

const VECTOR Player::RIGHT_ARM_POSITION = { -150.0f, 200.0f, -5.0f };

//�R���X�g���N�^
Player::Player() : PlayerBase()
	, rightArmHandle(0)
	, rightArmPosition()
{
	//�����Ȃ�
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
		inputDirection.z -= 1.0f;
		inputFlag = true;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		inputDirection.z += 1.0f;
		inputFlag = true;
	}
	//���E
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		inputDirection.x -= 1.0f;
		inputFlag = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		inputDirection.x += 1.0f;
		inputFlag = true;
	}

	//�\���L�[�̓��͂���������
	if (inputFlag)
	{
		//�\���L�[�̓��͕����𐳋K��
		inputDirection = VNorm(inputDirection);

		//�\���L�[�̈ړ������Ɉړ�
		position += inputDirection * SPEED * deltaTime;

		rightArmPosition += inputDirection * SPEED * deltaTime;
	}
}

//�`�揈��
void Player::Draw()
{
	MV1DrawModel(modelHandle);

	MV1DrawModel(rightArmHandle);
}