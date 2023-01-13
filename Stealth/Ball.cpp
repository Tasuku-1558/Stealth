#include "Ball.h"
#include "ModelManager.h"


const VECTOR Ball::SIZE		= { 2.0f, 2.0f, 2.0f };		//���f���̔{��
const VECTOR Ball::POSITION = { -1500.0f,30.0f,0.0f };	//���f���̈ʒu

Ball::Ball(VECTOR pos) : ObjectBase()
	, alive(true)
{
	position = pos;
}

Ball::~Ball()
{
	// �I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Ball::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BALL));
	MV1SetScale(modelHandle, SIZE);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [BALL]\n");
	}
}

void Ball::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Ball::Update(HitChecker* hitChecker)
{
	MV1SetPosition(modelHandle, position);

	IsAlive(hitChecker);
}

/// <summary>
/// �{�[�����A�N�e�B�u��
/// </summary>
void Ball::SetDead()
{
	alive = true;
	position = position;
}

/// <summary>
/// �����Ă邩����ł��邩
/// </summary>
/// <param name="hitChecker"></param>
void Ball::IsAlive(HitChecker* hitChecker)
{
	//���������Ȃ��
	if (hitChecker->Hit())
	{
		alive = false;

	}
	else
	{
		alive = true;
	}
}

void Ball::Draw()
{
	MV1DrawModel(modelHandle);
}