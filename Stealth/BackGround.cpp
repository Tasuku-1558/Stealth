#include "BackGround.h"
#include "Common.h"
#include "ModelManager.h"


const VECTOR BackGround::SIZE = { 10.0f, 10.0f, 10.0f };

BackGround::BackGround() : ObjectBase()
{
}

BackGround::~BackGround()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void BackGround::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE1));
	MV1SetScale(modelHandle, SIZE);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [PLAYER]\n");
	}
}

void BackGround::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void BackGround::Activate()
{
}

void BackGround::Update()
{
	MV1SetPosition(modelHandle, position);
}

void BackGround::Draw()
{
	MV1DrawModel(modelHandle);
}