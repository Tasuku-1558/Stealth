#include "Enemy.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Bullet.h"

const string Enemy::IMAGE_FOLDER_PATH = "data/image/";		//image�t�H���_�܂ł̃p�X
const string Enemy::SOUND_FOLDER_PATH = "data/sound/";		//sound�t�H���_�܂ł̃p�X
const string Enemy::PLAYER_FIND_PATH  = "playerFind.png";	//�v���C���[���������摜�̃p�X
const string Enemy::MARK_PATH		  = "mark.png";			//�r�b�N���}�[�N�摜�̃p�X
const string Enemy::CAKE_FIND_PATH	  = "cakeFind.png";		//�P�[�L���������摜�̃p�X
const string Enemy::CAKE_EAT_PATH	  = "cakeEat.png";		//�P�[�L��H�ׂĂ���摜�̃p�X
const string Enemy::SPOTTED_SE_PATH	  = "spotted.mp3";		//�v���C���[����SE���̃p�X


using namespace Math3d;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="id"></param>
Enemy::Enemy(std::vector<VECTOR>& id) : EnemyBase()
	, speedCount(0.0f)
	, cakeFindFlag(false)
	, cakeEatFlag(false)
{
	enemyState = EnemyState::CRAWL;
	Position(id);

	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void Enemy::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0 || visualModelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s[ENEMY]\n");
	}

	speed = SPEED;

	dir = ZERO_VECTOR;

	string failePath = IMAGE_FOLDER_PATH + PLAYER_FIND_PATH;
	playerFindImage = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + MARK_PATH;
	markImage = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + CAKE_FIND_PATH;
	cakeFindImage = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + CAKE_EAT_PATH;
	cakeEatImage = LoadGraph(failePath.c_str());

	failePath = SOUND_FOLDER_PATH + SPOTTED_SE_PATH;
	spottedSE = LoadSoundMem(failePath.c_str());
}

/// <summary>
/// ����������
/// </summary>
void Enemy::Activate()
{
	playerFindCount = 0;
	dir = ZERO_VECTOR;
	speed = SPEED;
}

/// <summary>
/// �G�l�~�[�ʒu�ݒ�
/// </summary>
/// <param name="num"></param>
void Enemy::Position(std::vector<VECTOR>& id)
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
	DeleteGraph(playerFindImage);
	DeleteGraph(markImage);
	DeleteGraph(cakeFindImage);
	DeleteGraph(cakeEatImage);

	//�T�E���h���\�[�X���폜
	InitSoundMem();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void Enemy::Update(float deltaTime, Player* player)
{
	//�G�l�~�[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);
	//MV1SetMaterialEmiColor(modelHandle, 0, GetColorF(0.5f, 0.0f, 0.0f, 1.0f));

	//�G�l�~�[�̎��샂�f�����Z�b�g
	MV1SetPosition(visualModelHandle, position);
	
	//�x�N�g���̐��K��
	dir = VNorm(targetPosition - position);
	
	position += dir * speed * deltaTime;

	VisualAnglePlayer(player);
	
	eUpdate(deltaTime);
	
	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	MV1SetRotationZYAxis(visualModelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

/// <summary>
/// �ړI�n�܂ňړ�����
/// </summary>
void Enemy::SetTargetPosition()
{
	targetPosition = *itr++;

	//�ŏI�ړI�n�ɓ��������玟�̖ړI�n�������ʒu�ɂ���
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
	return VSize(targetPosition - position) < SPEED * deltaTime;
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
			object = Object::PLAYER;

			//����͈͓��Ȃ��
			Reaction();
		}
	}
	else
	{
		playerSpotted = false;
	}
}

/// <summary>
/// �G�l�~�[�̎���Ƀ{�[�����������ꍇ
/// </summary>
/// <param name="bullet"></param>
/// <param name="deltaTime"></param>
void Enemy::VisualAngleBall(Bullet* bullet, float deltaTime)
{
	//�o���b�g����G�l�~�[�̍��W���������l���擾
	VECTOR sub = bullet->GetPosition() - position;

	//�o���b�g�ƃG�l�~�[��2�_�Ԃ̋������v�Z
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
		//�o���b�g���G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			object = Object::BALL;

			//����͈͓��Ȃ��
			Reaction();

			speedCount += deltaTime;

			cakeFindFlag = true;
			
			//�J�E���g��1.5�b�o�߂�����
			if (speedCount > 1.5f)
			{
				speed = SPEED;
				cakeFindFlag = false;
			}

			
			if (270.0f > direction)
			{
				speed = 0.0f;
				cakeEatFlag = true;
			}
		}
	}
	else
	{
		//�G�l�~�[�̎���͈͊O�Ȃ�X�s�[�h�����̃X�s�[�h�ɖ߂�
		speed = SPEED;

		ballFlag = false;

		cakeFindFlag = false;

		cakeEatFlag = false;

		//�J�E���g�̏�����
		speedCount = 0;
	}
}

/// <summary>
/// �G�l�~�[�̎���ɕǂ��������ꍇ
/// </summary>
/// <param name="wallPos"></param>
void Enemy::VisualAngleWall(VECTOR wallPos)
{
	//�ǂ���G�l�~�[�̍��W���������l���擾
	VECTOR sub = wallPos - position;

	//�ǂƃG�l�~�[��2�_�Ԃ̋������v�Z
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
		//�ǂ��G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			object = Object::WALL;

			//����͈͓��Ȃ��
			Reaction();
		}
	}
}

/// <summary>
/// �G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
/// </summary>
void Enemy::Reaction()
{
	switch (object)
	{
	case Object::PLAYER:
		printfDx("PLAYER");

		//�v���C���[�𔭌�����
		playerSpotted = true;
		
		//�r�b�N���}�[�N�̉摜��`��
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);

		//�G�Ɍ��������Ƃ���UI�摜��`��
		DrawGraph(50, 50, playerFindImage, TRUE);

		// ����SE���Đ�
		PlaySoundMem(spottedSE, DX_PLAYTYPE_BACK);
	
		
		playerFindCount++;
		break;

	case Object::BALL:
		//printfDx("BALL");

		//�{�[����������
		ballFlag = true;

		speed = 0.0f;

		
		break;

	case Object::WALL:
		printfDx("WALL");

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
			enemyState = EnemyState::ARRIVAL;
		}
			
		break;

	case EnemyState::ARRIVAL:
		SetTargetPosition();
		break;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Enemy::Draw()
{
	//�P�[�L���������Ȃ��
	if (cakeFindFlag)
	{
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 1200.0f, 0.0f, cakeFindImage, TRUE);
	}

	//�P�[�L�ɋ߂Â����Ȃ�
	if (cakeEatFlag)
	{
		DrawBillboard3D(VGet(position.x - 300.0f, 200.0f, position.z - 100.0f), 0.5f, 0.5f, 1200.0f, 0.0f, cakeEatImage, TRUE);
	}

	MV1DrawModel(modelHandle);

	MV1DrawModel(visualModelHandle);
}