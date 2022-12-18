#include "Enemy.h"
#include "ModelManager.h"
#include "Map.h"
#include "Common.h"


using namespace Math3d;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy() : EnemyBase()
	, targetPosition()
{
	enemyState = EnemyState::Crawl;
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

void Enemy::Initialize(Map* map)
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_BODY));

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s[ENEMY_BODY]\n");
	}

	Position(map);
}

/// <summary>
/// �G�l�~�[�ʒu�ݒ�
/// </summary>
void Enemy::Position(Map* map)
{
	pointList = map->GetMap(0);		//�}�b�v������W���X�g���󂯎��

	itr = pointList.begin();		//�C�e���[�^��擪�ɐݒ�

	position = *itr++;				//�C�e���[�^����G���W��ݒ�

	enemyState = EnemyState::Arrival;
}

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Activate()
{
}

void Enemy::Update(float deltaTime)
{
	//�G�l�~�[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);

	//�x�N�g���̐��K��
	dir = VNorm(targetPosition - position);

	position += dir * SPEED * deltaTime;

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

	enemyState = EnemyState::Crawl;
}

//�ړI�n�ɓ��B�����Ȃ��
bool Enemy::IsGoal(float deltaTime)
{
	return VSize(targetPosition - position) < SPEED * deltaTime;
}

//�G�l�~�[�̏��
void Enemy::eUpdate(float deltaTime)
{
	switch (enemyState)
	{
	case EnemyState::Crawl:

		if (IsGoal(deltaTime))
		{
			enemyState = EnemyState::Arrival;
		}
		break;

	case EnemyState::Arrival:
		SetTargetPosition();
		break;

	case EnemyState::Discovery:
		break;
	}
}

void Enemy::Draw()
{
	MV1DrawModel(modelHandle);
}