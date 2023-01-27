#include "Ball.h"
#include "ModelManager.h"
#include "HitChecker.h"


const VECTOR Ball::SIZE	= { 2.0f, 2.0f, 2.0f };		//���f���̔{��


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
Ball::Ball(VECTOR pos) : ObjectBase()
	, alive(true)
{
	position = pos;
	Initialize();
	Activate();
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

/// <summary>
/// ����������
/// </summary>
void Ball::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BALL));
	MV1SetScale(modelHandle, SIZE);
	MV1SetPosition(modelHandle, position);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [BALL]\n");
	}
}

/// <summary>
/// ����������
/// </summary>
void Ball::Activate()
{
	position = position;
}

/// <summary>
/// �I������
/// </summary>
void Ball::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// �X�V����
/// </summary>
void Ball::Update()
{
	//�����Ȃ�
}

/// <summary>
/// �{�[�����A�N�e�B�u��
/// </summary>
void Ball::BallAlive()
{
	alive = true;
	position = position;
}

/// <summary>
/// �{�[���������Ă邩����ł��邩�𔻒�
/// </summary>
/// <param name="hitChecker"></param>
void Ball::IsAlive(HitChecker* hitChecker)
{
	//�{�[���ɓ��������Ȃ��
	if (hitChecker->BallHit())
	{
		alive = false;
	}
	else
	{
		alive = true;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Ball::Draw()
{
	MV1DrawModel(modelHandle);
}