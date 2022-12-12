#include "Enemy.h"
#include "ModelManager.h"
#include "Common.h"
#include <math.h>

using namespace Math3d;

//�R���X�g���N�^
Enemy::Enemy() : EnemyBase()
{
	enemyState = EnemyState::Crawl;
}

//�f�X�g���N�^
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
}

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Activate()
{
	position = POSITION;
	dir = DIR;
}

void Enemy::Update(float deltaTime)
{
	GoBuck(deltaTime);

	//�G�l�~�[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);
}

void Enemy::GoBuck(float deltaTime)
{

	position += dir * SPEED * deltaTime;


	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g dir������
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
}

void Enemy::eUpdate()
{
	switch (enemyState)
	{
	case EnemyState::Crawl:
		break;

	case EnemyState::Tracking:
		break;

	}
}

void Enemy::Draw()
{
	eUpdate();

	MV1DrawModel(modelHandle);
}