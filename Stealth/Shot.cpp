#include "Shot.h"
#include <math.h>
#include "ModelManager.h"


const VECTOR Shot::SIZE  = { 2.0f, 2.0f, 2.0f };		//���f���̔{��
const float  Shot::SPEED = 200.0f;						//���f���̃X�s�[�h
const VECTOR Shot::DIR	 = { 1.0f,0.0f,0.0f };

using namespace Math3d;

Shot::Shot()
{
}

Shot::~Shot()
{
	// �I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Shot::Initialize()
{
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::BOAL);
	MV1SetScale(modelHandle, SIZE);


	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [BOAL]\n");
	}
}

void Shot::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Shot::Activate()
{
	dir = DIR;
}

void Shot::Update(VECTOR position)
{
	OnShot(position);
}

//���������ꂽ��
void Shot::OnShot(VECTOR position)
{
	//position += dir * SPEED;

	MV1SetPosition(modelHandle, position);
}

void Shot::Draw()
{
	MV1DrawModel(modelHandle);
}