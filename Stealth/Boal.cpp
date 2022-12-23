#include "Boal.h"
#include "ModelManager.h"
#include "HitChecker.h"


const VECTOR Boal::SIZE		= { 2.0f, 2.0f, 2.0f };		//���f���̔{��
const VECTOR Boal::POSITION = { -1500.0f,30.0f,0.0f };	//���f���̈ʒu

Boal::Boal() : ObjectBase()
	, alive(true)
{
	//�����Ȃ�
}

Boal::~Boal()
{
	// �I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Boal::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BOAL));
	MV1SetScale(modelHandle, SIZE);


	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [BOAL]\n");
	}
}

void Boal::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Boal::Activate()
{
	position = POSITION;
}

void Boal::Update()
{
	MV1SetPosition(modelHandle, position);
}

void Boal::Draw()
{
	MV1DrawModel(modelHandle);
}

/// <summary>
/// �����Ă邩����ł��邩
/// </summary>
/// <param name="hitChecker"></param>
void Boal::IsAlive(HitChecker* hitChecker)
{
	if (hitChecker->Hit())
	{
		alive = false;
	}
	else
	{
		alive = true;
	}
}