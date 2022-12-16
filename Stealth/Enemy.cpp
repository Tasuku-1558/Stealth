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

void Enemy::Position(Map* map)
{
	pointList = map->GetMap(0);		//�}�b�v������W���X�g���󂯎��

	itr = pointList.begin();		//�C�e���[�^��擪�ɐݒ�

	position = *itr;				//�C�e���[�^����G���W��ݒ�

	itr++;
}

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Activate()
{
	dir = DIR;
}

void Enemy::Update(float deltaTime)
{
	ActionPattern(deltaTime);

	//�G�l�~�[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �G�l�~�[�s���p�^�[��
/// </summary>
void Enemy::ActionPattern(float deltaTime)
{
	
	position += dir * SPEED * deltaTime;
	
	
	



	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g dir������
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

//�G�l�~�[�̏��
void Enemy::eUpdate()
{
	switch (enemyState)
	{
	case EnemyState::Crawl:
		break;

	case EnemyState::Arrival:
		break;

	case EnemyState::Discovery:
		break;
	}
}

void Enemy::Draw()
{
	eUpdate();

	MV1DrawModel(modelHandle);
}