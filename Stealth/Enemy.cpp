#include "Enemy.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Light.h"

const string Enemy::IMAGE_FOLDER_PATH = "data/image/";		//image�t�H���_�܂ł̃p�X
const string Enemy::SOUND_FOLDER_PATH = "data/sound/";		//sound�t�H���_�܂ł̃p�X
const string Enemy::FIND_PATH		  = "find.png";			//���������摜�̃p�X
const string Enemy::VIEW_RANGE_PATH	  = "view_range.png";
const string Enemy::MARK_PATH		  = "mark.png";			//�r�b�N���}�[�N�摜�̃p�X
const string Enemy::DISCOVERY_SE_PATH = "discovery.mp3";	//�v���C���[����SE���̃p�X


using namespace Math3d;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="num"></param>
Enemy::Enemy(std::vector<VECTOR>& num) : EnemyBase()
	, light(nullptr)
{
	enemyState = EnemyState::CRAWL;
	Position(num);

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

void Enemy::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s[ENEMY]\n");
	}

	speed = SPEED;

	dir = ZERO_VECTOR;

	light = new Light();

	string failePath = IMAGE_FOLDER_PATH + FIND_PATH;
	findImage = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + VIEW_RANGE_PATH;
	viewRangeImage = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + MARK_PATH;
	markImage = LoadGraph(failePath.c_str());

	failePath = SOUND_FOLDER_PATH + DISCOVERY_SE_PATH;
	discoverySE = LoadSoundMem(failePath.c_str());
}

void Enemy::Activate()
{
	playerFindCount = 0;
	dir = ZERO_VECTOR;
}

/// <summary>
/// �G�l�~�[�ʒu�ݒ�
/// </summary>
/// <param name="num"></param>
void Enemy::Position(std::vector<VECTOR>& num)
{
	pointList = num;				//�}�b�v������W���X�g���󂯎��

	itr = pointList.begin();		//�C�e���[�^��擪�ɐݒ�

	position = *itr++;				//�C�e���[�^����G���W��ݒ�

	enemyState = EnemyState::ARRIVAL;
}

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	DeleteGraph(findImage);
	DeleteGraph(markImage);

	// �T�E���h���\�[�X���폜
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
	
	//�x�N�g���̐��K��
	dir = VNorm(targetPosition - position);
	
	position += dir * speed * deltaTime;

	light->Update(dir);

	VisualAngle(player);

	VisualAngleBall(player);

	eUpdate(deltaTime);
	
	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

/// <summary>
/// �ړ�����
/// </summary>
void Enemy::SetTargetPosition()
{
	targetPosition = *itr++;

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
/// ����p�̌v�Z
/// </summary>
/// <param name="player"></param>
void Enemy::VisualAngle(Player* player)
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

	//�������Ă��Ȃ�
	discovery = false;
	
	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > direction)
	{
		//�v���C���[���G�l�~�[�̎���͈͓��ɂ��邩��r
		if (radian <= dot)
		{
			object = Object::PLAYER;
			
			//����͈͓��Ȃ��
			Reaction();
		}
	}
}

void Enemy::VisualAngleBall(Player* player)
{
	//�o���b�g����G�l�~�[�̍��W���������l���擾
	VECTOR sub = player->GetBulletPos() - position;

	//�o���b�g�ƃG�l�~�[��2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�x�N�g���̐��K��
	sub = VNorm(sub);

	//���όv�Z
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//�G�l�~�[�̎����cos�ɂ���
	float radian = cosf(range / 2.0f);

	ballFlag = false;

	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > direction)
	{
		//�o���b�g���G�l�~�[�̎���͈͓��ɂ��邩��r
		if (radian <= dot)
		{
			object = Object::BALL;

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
		discovery = true;

		//�r�b�N���}�[�N�̉摜��`��
		DrawBillboard3D(VGet(position.x - 300, 0.0f, position.z - 100), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);

		DrawGraph(300, 100, findImage, TRUE);		//�G�Ɍ��������Ƃ���UI�摜��`��

		// ����SE���Đ�
		PlaySoundMem(discoverySE, DX_PLAYTYPE_BACK);

		playerFindCount++;
		break;

	case Object::BALL:
		printfDx("BALL");
	
		ballFlag = true;
		if (ballFlag)
		{
			speed = 0.0f;
			count++;
			if (count > 200)
			{
				speed = SPEED;
				ballFlag = false;
				//count = 0;
				
			}
		}
		
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

	MV1DrawModel(modelHandle);

	/*VECTOR screenPos = ConvWorldPosToScreenPos(position);

	DrawBillboard3D(VGet(screenPos.z,screenPos.y,screenPos.x), 0.5f, 0.5f, 300.0f, DX_PI, viewRangeImage, TRUE);*/
}