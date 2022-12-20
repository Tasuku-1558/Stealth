#include "Player.h"
#include "PreCompiledHeader.h"
#include "Bullet.h"
#include "ModelManager.h"
#include "Camera.h"

using namespace Math3d;

const VECTOR Player::RIGHT_ARM_POSITION = { 150.0f, 0.0f, 110.0f };

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() : PlayerBase()
	, rightArmHandle(0)
	, rightArmPosition()
	, boalGet(false)
	, bullet(nullptr)
{
	playerState = PlayerState::Nomal;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	//�I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL || rightArmHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
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

	//�V���b�g�N���X
	bullet = new Bullet();
	bullet->Initialize();
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(rightArmHandle);
	rightArmHandle = NULL;

	bullet->Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Player::Activate()
{
	position = POSITION;
	rightArmPosition = RIGHT_ARM_POSITION;

	dir = DIR;

	bullet->Activate();
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update(float deltaTime, Camera* camera)
{
	Move(deltaTime, camera);

	Shoot();
	
	//�v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);

	MV1SetPosition(rightArmHandle, rightArmPosition);

}

/// <summary>
/// �ړ�����
/// </summary>
void Player::Move(float deltaTime, Camera* camera)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;
	
	//�㉺
	if (CheckHitKey(KEY_INPUT_UP))
	{
		inputDirection += camera->GetUp();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		inputDirection += camera->GetDown();
		inputFlag = true;
	}
	//���E
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		inputDirection += camera->GetRight();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		inputDirection += camera->GetLeft();
		inputFlag = true;
	}

	//�\���L�[�̓��͂���������
	if (inputFlag)
	{
		// ���E�E�㉺���������Ȃǂœ��̓x�N�g����0�̎�
		if (VSquareSize(inputDirection) < 0.5f)
		{
			return;
		}

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

/// <summary>
/// �e�̔��ˏ���
/// </summary>
void Player::Shoot()
{
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		bullet->Update();
	}
}

void Player::pUpdate()
{
	switch (playerState)
	{
	case PlayerState::Nomal:
		break;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{	
	MV1DrawModel(modelHandle);

	bullet->Draw();

	//MV1DrawModel(rightArmHandle);
}