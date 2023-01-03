#include "Player.h"
#include "PreCompiledHeader.h"
#include "Bullet.h"
#include "ModelManager.h"
#include "Camera.h"
#include "Ball.h"
#include "Enemy.h"
#include "HitChecker.h"

using namespace Math3d;

const VECTOR Player::RIGHT_ARM_POSITION = { 150.0f, 0.0f, 110.0f };

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="PLAYER"></param>
Player::Player(Object PLAYER) : PlayerBase()
	, rightArmHandle(0)
	, rightArmPosition()
	, bullet(nullptr)
{
	cursor = Cursor::SELECTION;
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
	bullet = new Bullet(ObjectBase::BALL);
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

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="ball"></param>
void Player::Update(float deltaTime, Camera* camera, Ball* ball, Enemy* enemy, HitChecker* hitChecker)
{
	Move(deltaTime, camera);

	Shoot(deltaTime, ball);

	FoundEnemy(enemy);

	aa(hitChecker);

	cUpdate(ball);
	
	//�v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);

	MV1SetPosition(rightArmHandle, rightArmPosition);

	bullet->Activate();

}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
void Player::Move(float deltaTime, Camera* camera)
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
		position += inputDirection * SPEED * deltaTime;

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
/// <param name="deltaTime"></param>
/// <param name="ball"></param>
void Player::Shoot(float deltaTime, Ball* ball)
{
	//�}�E�X�J�[�\�������N���b�N�����Ȃ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		bullet->Update(deltaTime, ball);
		cursor = Cursor::PUSH;
		
		
	}

	bullet->MouseMove(ball);
}

/// <summary>
/// �G�l�~�[�Ɍ��������ꍇ
/// </summary>
/// <param name="enemy"></param>
void Player::FoundEnemy(Enemy* enemy)
{
	if (enemy->Discovery())
	{
		WaitTimer(1000);

		//�ʒu�ƌ�����������
		position = ZERO_VECTOR;
		dir = DIR;
	}
}

void Player::aa(HitChecker* hitChecker)
{
	if (hitChecker->ai())
	{
		
	}
}

void Player::cUpdate(Ball* ball)
{
	switch (cursor)
	{
	case Cursor::SELECTION:
		break;

	case Cursor::PUSH:
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

	//�f�o�b�N�p
	DrawFormatString(100, 500, GetColor(255, 0, 0), "mouseX : %d", bullet->GetMX());
	DrawFormatString(100, 600, GetColor(255, 0, 0), "mouseY : %d", bullet->GetMY());

}