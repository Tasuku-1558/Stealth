#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "Enemy.h"

using namespace Math3d;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() : PlayerBase()
	, count(0)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	//�I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s[PLAYER]\n");
	}
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// ����������
/// </summary>
void Player::Activate()
{
	position = POSITION;
	previewPosition = POSITION;
	dir = DIR;
	speed = SPEED;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Update(float deltaTime, Camera* camera, VECTOR back, bool mapHit)
{
	Move(deltaTime, camera, back, mapHit);

	//�v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	//�㉺
	if (CheckHitKey(KEY_INPUT_W))
	{
		inputDirection += camera->GetUp();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		inputDirection += camera->GetDown();
		inputFlag = true;
	}
	//���E
	if (CheckHitKey(KEY_INPUT_D))
	{
		inputDirection += camera->GetRight();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_A))
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
		previewPosition += dir * speed * deltaTime;

		//�}�b�v�Ƀv���C���[���Փ˂����Ȃ��
		if (mapHit)
		{
			//�����̈ʒu�ɉ����߂��̒l��������
			previewPosition = back;

			position = previewPosition;
			previewPosition = position;
		}
		else
		{
			position = previewPosition;
			previewPosition = position;
		}
	}

	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g dir������
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

/// <summary>
/// �G�l�~�[�Ɍ��������ꍇ
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="enemy"></param>
void Player::FoundEnemy(float deltaTime, Enemy* enemy)
{
	//�G�l�~�[�Ɍ���������
	if (enemy->Spotted())
	{
		WaitTimer(1000);

		//�ʒu�ƌ�����������
		position = POSITION;
		previewPosition = POSITION;
		dir = DIR;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{	
	MV1DrawModel(modelHandle);
}