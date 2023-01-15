#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace Math3d;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="PLAYER"></param>
Player::Player(Object PLAYER) : PlayerBase()
	, bullet(nullptr)
	, bulletCount(0.0f)
	, bulletPosition()
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

	bullet->Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Player::Activate()
{
	position = POSITION;
	dir = DIR;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="ball"></param>
/// <param name="enemy"></param>
void Player::Update(float deltaTime, Camera* camera/*, Ball* ball, Enemy* enemy*/)
{
	Move(deltaTime, camera);

	//�v���C���[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);
	
}

void Player::BallUpdate(float deltaTime, Ball* ball)
{
	Shoot(deltaTime, ball);

	BulletReuse(deltaTime, ball);
}

void Player::EnemyUpdate(Enemy* enemy)
{
	FoundEnemy(enemy);
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
}

/// <summary>
/// �e�̔��ˏ���
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="ball"></param>
void Player::Shoot(float deltaTime, Ball* ball)
{
	//�}�E�X�J�[�\�������N���b�N���A���{�[���ƃo���b�g����A�N�e�B�u�Ȃ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && !ball->GetAlive())
	{
		bullet->Update(deltaTime, ball);
		bullet->SetAlive();
		bulletPosition = bullet->GetPosition();
	}
	
	bullet->MouseMove(ball, position);
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
		position = POSITION;
		dir = DIR;
	}
}

/// <summary>
/// �o���b�g�Ďg�p�J�E���g
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="ball"></param>
void Player::BulletReuse(float deltaTime, Ball* ball)
{
	if (bullet->GetAlive())
	{
		bulletCount += deltaTime;
	}

	//�J�E���g��5�b�ȏ�o�߂�����
	if (bulletCount > 5.0f)
	{
		bulletCount = 0.0f;
		bulletPosition = ZERO_VECTOR;

		ball->SetDead();
		bullet->SetDead();
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{	
	MV1DrawModel(modelHandle);

	bullet->Draw();
}