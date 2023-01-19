#include "Ball.h"
#include "ModelManager.h"


const VECTOR Ball::SIZE		= { 2.0f, 2.0f, 2.0f };		//���f���̔{��


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
Ball::Ball(VECTOR pos) : ObjectBase()
	, alive(true)
{
	position = pos;
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
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

void Ball::Update()
{
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �{�[�����A�N�e�B�u��
/// </summary>
void Ball::SetAlive()
{
	alive = true;
	position = position;
}

/// <summary>
/// �����Ă邩����ł��邩
/// </summary>
/// <param name="hit"></param>
void Ball::IsAlive(bool hit)
{
	//���������Ȃ��
	if (hit)
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