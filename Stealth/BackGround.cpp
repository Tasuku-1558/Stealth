#include "BackGround.h"
#include "Common.h"
#include "ModelManager.h"


const VECTOR BackGround::SIZE	  = { 30.0f, 10.0f, 30.0f };		//���f���̔{��
const VECTOR BackGround::POSITION = { -1500.0f, 0.0f, 0.0f };		//���f���̈ʒu

BackGround::BackGround() : ObjectBase()
{
	//�����Ȃ�
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
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));

	position = POSITION;

	MV1SetPosition(modelHandle, position);

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

void BackGround::Draw()
{
	MV1DrawModel(modelHandle);
}