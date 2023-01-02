#include "Enemy.h"
#include "ModelManager.h"
#include "Map.h"
#include "Player.h"


const string Enemy::IMAGE_FOLDER_PATH = "data/image/";     //image�t�H���_�܂ł̃p�X
const string Enemy::FIND_PATH = "a.png";		//�J�[�\���摜�̃p�X


using namespace Math3d;
using namespace std;

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="map"></param>
Enemy::Enemy(Map* map) : EnemyBase()
	, object()
	, targetPosition()
	, length(400.0f)
	, discovery(false)
	, playerFindCount(0)
	, findImage(0)
{
	enemyState = EnemyState::CRAWL;
	Position(map);
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
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_BODY));

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s[ENEMY_BODY]\n");
	}

	string failePath = IMAGE_FOLDER_PATH + FIND_PATH;
	findImage = LoadGraph(failePath.c_str());
}

/// <summary>
/// �G�l�~�[�ʒu�ݒ�
/// </summary>
/// <param name="map"></param>
void Enemy::Position(Map* map)
{
	pointList = map->GetMap(0);		//�}�b�v������W���X�g���󂯎��

	itr = pointList.begin();		//�C�e���[�^��擪�ɐݒ�

	position = *itr++;				//�C�e���[�^����G���W��ݒ�

	enemyState = EnemyState::ARRIVAL;
}

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	DeleteGraph(findImage);
}

void Enemy::Activate()
{
}

void Enemy::Update(float deltaTime, Player* player)
{
	//�G�l�~�[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);
	
	//�x�N�g���̐��K��
	dir = VNorm(targetPosition - position);
	
	//position += dir * SPEED * deltaTime;

	VisualAngle(player);

	eUpdate(deltaTime);

	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g dir������
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
	//�v���C���[�ƃG�l�~�[�̋������擾
	VECTOR sub = player->GetPosition() - position;

	//������float�ɒu������
	float direction = VSize(sub);

	//�G�l�~�[�̑O���ƃv���C���[�̈ʒu�̊p�x
	float radian = VDot(player->GetPosition(), dir);

	//float a = RANGE_DEGREE * (float)(DX_PI / 180.0f);
	//float b = radian * (float)(DX_PI / 180.0f);


	float range_Cos = cosf(RANGE_DEGREE * (float)(DX_PI / 180.0f));
	float radian_Cos = cosf(radian * (float)(DX_PI / 180.0f));

	discovery = false;
	

	// �������Ă��邩�ǂ���
	if (length > direction)
	{
		//printfDx("���G�͈͓�");

		//�v���C���[�𔭌�
		if (radian_Cos <= range_Cos)
		{
			//printfDx("����");
			
			Reaction(object);
		}
	}
}

/// <summary>
/// �G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
/// </summary>
/// <param name="object"></param>
void Enemy::Reaction(Object object)
{
	switch (object)
	{
	case ObjectBase::PLAYER:
		printfDx("PLAYER");
		discovery = true;

		DrawGraph(0, -50, findImage, TRUE);
		playerFindCount++;
		break;

	case ObjectBase::BALL:
		printfDx("BALL");
		break;

	case ObjectBase::WALL:
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
}