#include "Enemy.h"
#include "ModelManager.h"
#include "InputManager.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="movePattern">�s���p�^�[���̔ԍ�</param>
/// <param name="enemySpeed">�G�l�~�[�̃X�s�[�h</param>
Enemy::Enemy(int movePattern, float enemySpeed)
	: enemyReaction(EnemyReaction::NORMAL)
	, cakeCount(0.0f)
	, cakeFindFlag(false)
	, rotateFlag(false)
	, cakeEat(false)
	, nextDirection()
	, IMAGE_FOLDER_PATH("Data/Image/")
	, MARK_PATH("mark.png")
{
	Position(GetList(movePattern));

	changeSpeed = enemySpeed;

	Initialize();
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
	//�G�l�~�[���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	//���샂�f���̓ǂݍ���
	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//�r�b�N���}�[�N�摜�̓ǂݍ���
	markImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());

	speed = changeSpeed;

	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// �G�l�~�[�ʒu�ݒ�
/// </summary>
/// <param name="id">�G�̍s���p�^�[�����X�g</param>
void Enemy::Position(vector<VECTOR>& id)
{
	pointList = id;					//���W���X�g���󂯎��

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
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
/// <param name="playerPosition">�v���C���[�̍��W</param>
void Enemy::Update(float deltaTime, VECTOR playerPosition)
{
	StateUpdate(deltaTime);

	Move(deltaTime);

	VisualAnglePlayer(playerPosition);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Enemy::Move(float deltaTime)
{
	if (enemyState == EnemyState::CRAWL || enemyState == EnemyState::ARRIVAL)
	{
		//���݂̌���
		direction = VNorm(targetPosition - position);
	}
	
	if (enemyState == EnemyState::ROTATION)
	{
		//���݂̌���
		direction = VNorm(direction);

		//�ڕW�̌���
		nextDirection = VNorm(targetPosition - position);
	}

	position += direction * speed * deltaTime;

	//�G�l�~�[�̈ʒu�ƌ������Z�b�g
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, direction, Y_ANGLE);

	//����̈ʒu�ƌ������Z�b�g
	MV1SetPosition(visualModelHandle, position);
	MV1SetRotationYUseDir(visualModelHandle, direction, Y_ANGLE);

	//�����蔻�苅�̈ړ�����
	collisionSphere.Move(position);
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
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
/// <returns></returns>
bool Enemy::IsGoal(float deltaTime)
{
	return VSize(targetPosition - position) < speed * deltaTime;
}

/// <summary>
/// �G�l�~�[�̉�]����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Enemy::EnemyRotate(float deltaTime)
{
	//�G�l�~�[����]�����邩
	if (rotateFlag)
	{
		//��]���ڕW�p�x�ɏ\���߂���Ή�]����߂�
		if (IsNearAngle(nextDirection, direction))
		{
			direction = nextDirection;
			rotateFlag = false;
		}
		else
		{
			//��]������
			VECTOR interPolateDir = RotateForAimVecYAxis(direction, nextDirection, Y_ANGLE_SPEED);

			//��]���ڕW�p�x�𒴂��Ă��Ȃ���
			VECTOR cross1 = VCross(direction, nextDirection);
			VECTOR cross2 = VCross(interPolateDir, nextDirection);

			//�ڕW�p�x�𒴂�����I��
			if (cross1.y * cross2.y < TARGET_ANGLE)
			{
				interPolateDir = nextDirection;
				rotateFlag = false;
			}

			//�ڕW�x�N�g����10�x�����߂Â����p�x
			direction = interPolateDir;
		}
	}

	EnemyRotateTime(deltaTime);
}

/// <summary>
/// �G�l�~�[�̉�]�̎���
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Enemy::EnemyRotateTime(float deltaTime)
{
	rotateTime += deltaTime;

	RotateTime rotate[] =
	{
		{EnemyReaction::NORMAL, NOMAL_ROTATE_TIME},
		{EnemyReaction::PLAYER, PLAYER_ROTATE_TIME},
		{EnemyReaction::CAKE,	CAKE_ROTATE_TIME},
	};

	for (int i = 0; i < ROTATE_TIME_CATEGORY; i++)
	{
		//�e�I�u�W�F�N�g�ɂ���ĉ�]�̎��Ԃ�ς���
		if (enemyReaction == rotate[i].enemyReaction && rotateTime > rotate[i].time)
		{
			//�X�s�[�h�����ɖ߂�
			speed = changeSpeed;

			rotateTime = INITIAL_ROTATE_TIME;

			enemyState = EnemyState::ARRIVAL;
		}
	}
}

/// <summary>
/// �G�l�~�[�̎���Ƀv���C���[���������ꍇ
/// </summary>
/// <param name="playerPosition">�v���C���[�̍��W</param>
void Enemy::VisualAnglePlayer(VECTOR playerPosition)
{
	//�v���C���[����G�l�~�[�̍��W���������l���擾
	VECTOR sub = playerPosition - position;

	//�v���C���[�ƃG�l�~�[�̋������v�Z
	playerDirection = VSize(sub);

	//�x�N�g���̐��K��
	sub = VNorm(sub);

	//���όv�Z
	float dot = VDot(sub, direction);

	float range = RANGE_DEGREE * (DX_PI_F / 180.0f);

	//�G�l�~�[�̎����cos�ɂ���
	float radian = cosf(range / 2.0f);

	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > playerDirection)
	{
		//�v���C���[���G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			enemyReaction = EnemyReaction::PLAYER;

			direction = sub;

			Reaction();
		}
	}
	else
	{
		playerSpotted = false;

		enemyReaction = EnemyReaction::NORMAL;
	}
}

/// <summary>
/// �G�l�~�[�̎���ɃP�[�L���������ꍇ
/// </summary>
/// <param name="bulletPosition">�o���b�g�̍��W</param>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Enemy::VisualAngleCake(VECTOR bulletPosition, float deltaTime)
{
	//�o���b�g����G�l�~�[�̍��W���������l���擾
	VECTOR sub = bulletPosition - position;

	//�o���b�g�ƃG�l�~�[�̋������v�Z
	bulletDirection = VSize(sub);

	//�x�N�g���̐��K��
	sub = VNorm(sub);

	//���όv�Z
	float dot = VDot(sub, direction);

	float range = RANGE_DEGREE * (DX_PI_F / 180.0f);

	//�G�l�~�[�̎����cos�ɂ���
	float radian = cosf(range / 2.0f);
	
	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > bulletDirection)
	{
		//�o���b�g���G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			enemyReaction = EnemyReaction::CAKE;

			direction = sub;

			Reaction();

			CakeEatCount(deltaTime);
		}
	}
	else
	{
		//�G�l�~�[�̎���͈͊O�Ȃ�X�s�[�h�����̃X�s�[�h�ɖ߂�
		speed = changeSpeed;

		cakeFlag = false;

		cakeFindFlag = false;

		cakeEat = false;

		//�J�E���g�̏�����
		cakeCount = 0.0f;

		enemyReaction = EnemyReaction::NORMAL;
	}
}

/// <summary>
/// �b���ɂ���ăP�[�L�̏�ԕω�
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
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
	if (/*230.0f > bulletDirection*/!cakeFindFlag)
	{
		speed = STOP_SPEED;

		cakeEat = true;
	}
}

/// <summary>
/// �G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
/// </summary>
void Enemy::Reaction()
{
	switch (enemyReaction)
	{
	case EnemyReaction::NORMAL:
		break;

	case EnemyReaction::PLAYER:

		//�v���C���[�𔭌�����
		playerSpotted = true;

		break;

	case EnemyReaction::CAKE:

		cakeFlag = true;

		//�P�[�L��������
		cakeFindFlag = true;

		//�G�l�~�[�̓������~�߂�
		speed = STOP_SPEED;
		
		break;
	}
}

/// <summary>
/// �G�l�~�[�̏�Ԃ̕ω�
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Enemy::StateUpdate(float deltaTime)
{
	switch (enemyState)
	{
	case EnemyState::CRAWL:

		//�ړI�n�ɂ��ǂ蒅�����Ȃ��
		if (IsGoal(deltaTime))
		{
			targetPosition = *itr;

			//�ŏI�ړI�n�ɓ��������玟�̖ړI�n�Ɍ�����
			if (itr == pointList.end())
			{
				itr = pointList.begin();
			}

			enemyState = EnemyState::ROTATION;
		}

		break;

	case EnemyState::ARRIVAL:
		SetTargetPosition();
		break;

	case EnemyState::ROTATION:
		
		//�G�l�~�[�̓������~�߂�
		speed = STOP_SPEED;

		//�G�l�~�[����]������
		rotateFlag = true;
		
		EnemyRotate(deltaTime);

		break;
	}
}

/// <summary>
/// �v���C���[�ƏՓ˂���
/// </summary>
void Enemy::HitPlayer()
{
	playerSpotted = true;
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
		speed = STOP_SPEED;

		//�r�b�N���}�[�N�̉摜��`��
		DrawBillboard3D(VGet(position.x - 200.0f, 0.0f, position.z + 200.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//�P�[�L���������Ȃ��
	if (cakeFindFlag)
	{
		//�r�b�N���}�[�N�摜��`��
		DrawBillboard3D(VGet(position.x - 200.0f, 0.0f, position.z + 200.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
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