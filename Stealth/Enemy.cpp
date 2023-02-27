#include "Enemy.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Bullet.h"
#include "HitChecker.h"

using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="id"></param>
/// <param name="enemySpeed"></param>
Enemy::Enemy(vector<VECTOR>& id, float enemySpeed) : EnemyBase()
	, cakeCount(0.0f)
	, cakeFindFlag(false)
	, cakeEatFlag(false)
	, cakeHalfFlag(false)
	, IMAGE_FOLDER_PATH("data/image/")
	, MARK_PATH("mark.png")
	, CAKE_PATH("ui8.png")
	, CAKE_HALF_PATH("cakeHalf.png")
	, dira()
{
	//enemyState = EnemyState::CRAWL;

	Position(id);

	changeSpeed = enemySpeed;

	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Enemy::Initialize()
{
	//���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//�摜�̓ǂݍ���
	markImage	 = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());

	cakeImage[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, CAKE_PATH).c_str());

	cakeImage[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, CAKE_HALF_PATH).c_str());
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string Enemy::InputPath(string folderPath, string imagePath)
{
	return string(folderPath + imagePath);
}

/// <summary>
/// ����������
/// </summary>
void Enemy::Activate()
{
	speed = changeSpeed;
	dir = ZERO_VECTOR;
	dira = ZERO_VECTOR;
	playerSpotted = false;
	cakeFlag = false;
	cakeFindFlag = false;
	cakeEatFlag = false;
	cakeHalfFlag = false;
	cakeCount = 0.0f;
}

/// <summary>
/// �G�l�~�[�ʒu�ݒ�
/// </summary>
/// <param name="id"></param>
void Enemy::Position(vector<VECTOR>& id)
{
	pointList = id;					//�}�b�v������W���X�g���󂯎��

	itr = pointList.begin();		//�C�e���[�^��擪�ɐݒ�

	position = *itr++;				//�C�e���[�^����G���W��ݒ�

	enemyState = EnemyState::ARRIVAL;
}

/// <summary>
/// �I������
/// </summary>
void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(visualModelHandle);

	DeleteGraph(markImage);

	for (int i = 0; i < CAKE_IMAGE_NUMBER; i++)
	{
		DeleteGraph(cakeImage[i]);
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
/// <param name="hitChecker"></param>
void Enemy::Update(float deltaTime, Player* player, HitChecker* hitChecker)
{
	eUpdate(deltaTime);

	Move(deltaTime);

	VisualAnglePlayer(player);

	//�G�l�~�[�Ƀv���C���[���Փ˂����Ȃ��
	if (hitChecker->EnemyHit())
	{
		playerSpotted = true;
	}
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
void Enemy::Move(float deltaTime)
{
	if (enemyState == EnemyState::CRAWL || enemyState == EnemyState::ARRIVAL)
	{
		//�x�N�g���̐��K��
		dir = VNorm(targetPosition - position);
	}
	
	if (enemyState == EnemyState::ROTATION)
	{
		//�x�N�g���̐��K��
		dir = VNorm(dir);

		dira = VNorm(targetPosition - position);

		if (dira.x != dir.x || dira.z != dira.z)
		{
			dir += dira;
		}

	}

	position += dir * speed * deltaTime;

	//�G�l�~�[�̈ʒu�ƌ������Z�b�g
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, dir, 0.0f);

	//�G�l�~�[�̎��샂�f���̈ʒu�ƌ������Z�b�g
	MV1SetPosition(visualModelHandle, position);
	MV1SetRotationYUseDir(visualModelHandle, dir, 0.0f);
}

/// <summary>
/// �ړI�n�܂ňړ�����
/// </summary>
void Enemy::SetTargetPosition()
{
	targetPosition = *itr++;

	//�ŏI�ړI�n�ɓ��������玟�̖ړI�n�Ɍ�����
	if (itr == pointList.end())
	{
		itr = pointList.begin();
	}

	enemyState = EnemyState::CRAWL;
}

/// <summary>
/// �ړI�n�ɓ��B�����Ȃ��
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
bool Enemy::IsGoal(float deltaTime)
{
	return VSize(targetPosition - position) < speed * deltaTime;
}

/// <summary>
/// �G�l�~�[�̎���Ƀv���C���[���������ꍇ
/// </summary>
/// <param name="player"></param>
void Enemy::VisualAnglePlayer(Player* player)
{
	//�v���C���[����G�l�~�[�̍��W���������l���擾
	VECTOR sub = player->GetPosition() - position;

	//�v���C���[�ƃG�l�~�[��2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�x�N�g���̐��K��
	sub = VNorm(sub);

	//���όv�Z
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//�G�l�~�[�̎����cos�ɂ���
	float radian = cosf(range / 2.0f);

	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > direction)
	{
		//�v���C���[���G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			enemyReaction = EnemyReaction::PLAYER;

			//����͈͓��Ȃ��
			Reaction();

			dir = sub;
		}
	}
	else
	{
		dir = dir;
		playerSpotted = false;
	}
}

/// <summary>
/// �G�l�~�[�̎���ɃP�[�L���������ꍇ
/// </summary>
/// <param name="bullet"></param>
/// <param name="deltaTime"></param>
void Enemy::VisualAngleCake(Bullet* bullet, float deltaTime)
{
	//�o���b�g����G�l�~�[�̍��W���������l���擾
	VECTOR sub = bullet->GetPosition() - position;

	//�o���b�g�ƃG�l�~�[��2�_�Ԃ̋������v�Z
	bulletDirection = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�x�N�g���̐��K��
	sub = VNorm(sub);

	//���όv�Z
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//�G�l�~�[�̎����cos�ɂ���
	float radian = cosf(range / 2.0f);
	
	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > bulletDirection)
	{
		//�o���b�g���G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			enemyReaction = EnemyReaction::CAKE;

			//����͈͓��Ȃ��
			Reaction();

			dir = sub;

			CakeEatCount(deltaTime);
		}
	}
	else
	{
		//�G�l�~�[�̎���͈͊O�Ȃ�X�s�[�h�����̃X�s�[�h�ɖ߂�
		speed = changeSpeed;

		cakeFlag = false;

		cakeFindFlag = false;

		cakeEatFlag = false;

		cakeHalfFlag = false;

		//�J�E���g�̏�����
		cakeCount = 0.0f;

		dir = dir;
	}
}

/// <summary>
/// �b���ɂ���ăP�[�L�̏�ԕω�
/// </summary>
/// <param name="deltaTime"></param>
void Enemy::CakeEatCount(float deltaTime)
{
	cakeCount += deltaTime;

	//�P�[�L�������ăJ�E���g��1.5�b�o�߂�����
	if (cakeCount > 1.5f)
	{
		speed = changeSpeed;

		//�r�b�N���}�[�N�摜���\���ɂ���
		cakeFindFlag = false;
	}

	//�r�b�N���}�[�N�摜����\���ɂȂ�����
	//�P�[�L�̉摜��\������
	if (230.0f > bulletDirection)
	{
		speed = 0.0f;
		cakeEatFlag = true;

		//�J�E���g��4�b�o�߂�����
		//�����ɂȂ����P�[�L�̉摜��\������
		if (cakeCount > 4.0f)
		{
			cakeEatFlag = false;

			cakeHalfFlag = true;
		}
	}
}

/// <summary>
/// �G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
/// </summary>
void Enemy::Reaction()
{
	switch (enemyReaction)
	{
	case EnemyReaction::PLAYER:

		//�v���C���[�𔭌�����
		playerSpotted = true;

		break;

	case EnemyReaction::CAKE:

		cakeFlag = true;

		//�P�[�L��������
		cakeFindFlag = true;

		//�G�l�~�[�̓������~�߂�
		speed = 0.0f;
		
		break;
	}
}

/// <summary>
/// �G�l�~�[�̏��
/// </summary>
/// <param name="deltaTime"></param>
void Enemy::eUpdate(float deltaTime)
{
	switch (enemyState)
	{
	case EnemyState::CRAWL:

		if (IsGoal(deltaTime))
		{
			//enemyState = EnemyState::ARRIVAL;

			enemyState = EnemyState::ROTATION;
		}
			
		break;

	case EnemyState::ARRIVAL:
		SetTargetPosition();
		break;

	case EnemyState::ROTATION:

		//�G�l�~�[�̓������~�߂�
		speed = 0.0f;

		
		if (CheckHitKey(KEY_INPUT_G))
		{
			speed = changeSpeed;
			enemyState = EnemyState::ARRIVAL;
		}

		break;
	}
}

/// <summary>
/// ���A�N�V�����摜�̕`�揈��
/// </summary>
void Enemy::ReactionDraw()
{
	//�v���C���[����������
	if (playerSpotted)
	{
		//�G�l�~�[�̓������~�߂�
		speed = 0.0f;

		//�r�b�N���}�[�N�̉摜��`��
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//�P�[�L���������Ȃ��
	if (cakeFindFlag)
	{
		//�r�b�N���}�[�N�摜��`��
		DrawBillboard3D(VGet(position.x - 300.0f, 400.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//�P�[�L���G�l�~�[�̎���p�ɓ������Ȃ��
	if (cakeEatFlag)
	{
		//�P�[�L�̉摜��`��
		DrawBillboard3D(VGet(position.x + 100.0f, 500.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, cakeImage[0], TRUE);
	}

	//�P�[�L���G�l�~�[�̎���p�ɓ�����4�b�o�߂�����
	if (cakeHalfFlag)
	{
		//�P�[�L�������̉摜��`��
		DrawBillboard3D(VGet(position.x + 100.0f, 500.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, cakeImage[1], TRUE);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::Draw()
{
	MV1DrawModel(modelHandle);

	MV1DrawModel(visualModelHandle);

	ReactionDraw();
}