#include "Enemy.h"
#include "ModelManager.h"
#include "Player.h"
#include "Bullet.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="number">�s���p�^�[���̔ԍ�</param>
/// <param name="enemySpeed">�G�l�~�[�̃X�s�[�h</param>
Enemy::Enemy(int number, float enemySpeed)
	: EnemyBase()
	, cakeCount(0.0f)
	, cakeFindFlag(false)
	, IMAGE_FOLDER_PATH("Data/image/")
	, MARK_PATH("mark.png")
	, nextDirection()
	, rotateFlag(false)
	, frame(0.0f)
	, cakeEat(false)
	, enemyReaction(EnemyReaction::NORMAL)
{
	Position(GetList(number));

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
	//�G�l�~�[���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	//���샂�f���̓ǂݍ���
	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//�r�b�N���}�[�N�摜�̓ǂݍ���
	markImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="imagePath"></param>
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
	direction = ZERO_VECTOR;
	nextDirection = ZERO_VECTOR;

	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
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
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Enemy::Update(float deltaTime, Player* player)
{
	StateUpdate(deltaTime);

	Move(deltaTime);

	VisualAnglePlayer(player);

	//�����蔻�苅�̈ړ�����
	collisionSphere.Move(position);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
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
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);

	//����̈ʒu�ƌ������Z�b�g
	MV1SetPosition(visualModelHandle, position);
	MV1SetRotationYUseDir(visualModelHandle, direction, 0.0f);
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
/// �G�l�~�[�̉�]����
/// </summary>
/// <param name="deltaTime"></param>
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
			VECTOR interPolateDir = RotateForAimVecYAxis(direction, nextDirection, 4.0f);

			//��]���ڕW�p�x�𒴂��Ă��Ȃ���
			VECTOR cross1 = VCross(direction, nextDirection);
			VECTOR cross2 = VCross(interPolateDir, nextDirection);

			//�ڕW�p�x�𒴂�����I��
			if (cross1.y * cross2.y < 0.0f)
			{
				interPolateDir = nextDirection;
				rotateFlag = false;
			}

			//�ڕW�x�N�g����10�x�����߂Â����p�x
			direction = interPolateDir;
		}
	}

	frame += deltaTime;

	//�e�I�u�W�F�N�g�ɂ���ăJ�E���g�̎��Ԃ�ς���
	if (enemyReaction == EnemyReaction::NORMAL && frame > 1.0f ||
		enemyReaction == EnemyReaction::PLAYER && frame > 2.0f||
		enemyReaction == EnemyReaction::CAKE && frame > 6.0f)
	{
		//�X�s�[�h�����ɖ߂�
		speed = changeSpeed;

		frame = 0.0f;

		enemyState = EnemyState::ARRIVAL;
	}
}

/// <summary>
/// �G�l�~�[�̎���Ƀv���C���[���������ꍇ
/// </summary>
/// <param name="player"></param>
void Enemy::VisualAnglePlayer(Player* player)
{
	//�v���C���[����G�l�~�[�̍��W���������l���擾
	VECTOR sub = player->GetPosition() - position;

	//�v���C���[�ƃG�l�~�[�̋������v�Z
	float playerDirection = VSize(sub);

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
/// <param name="bullet"></param>
/// <param name="deltaTime"></param>
void Enemy::VisualAngleCake(Bullet* bullet, float deltaTime)
{
	//�o���b�g����G�l�~�[�̍��W���������l���擾
	VECTOR sub = bullet->GetPosition() - position;

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
	if (/*230.0f > bulletDirection*/!cakeFindFlag)
	{
		speed = 0.0f;

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
		speed = 0.0f;
		
		break;
	}
}

/// <summary>
/// �G�l�~�[�̓���
/// </summary>
/// <param name="deltaTime"></param>
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
		speed = 0.0f;

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
		speed = 0.0f;

		//�r�b�N���}�[�N�̉摜��`��
		DrawBillboard3D(VGet(position.x - 200.0f, 0.0f, position.z + 200.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//�P�[�L���������Ȃ��
	if (cakeFindFlag)
	{
		//�r�b�N���}�[�N�摜��`��
		DrawBillboard3D(VGet(position.x - 200.0f, 400.0f, position.z + 200.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
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