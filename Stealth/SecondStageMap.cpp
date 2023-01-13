#include "SecondStageMap.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR SecondStageMap::SIZE	 = { 80.0f, 50.0f, 80.0f };					//���f���̔{��
const VECTOR SecondStageMap::POSITION = { -200.0f, 50.0f, 1350.0f };				//���f���̈ʒu

using namespace std;

SecondStageMap::SecondStageMap() : ObjectBase()
{
	//�����Ȃ�
}

SecondStageMap::~SecondStageMap()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void SecondStageMap::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE2));
	MV1SetScale(modelHandle, SIZE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [STAGE1]\n");
	}

	MapList();
	MapList2();
}

void SecondStageMap::MapList()
{
	positionList.push_back(VGet(-2300.0f, 100.0f, 500.0f));
	positionList.push_back(VGet(-2300.0f, 100.0f, -500.0f));
	positionList.push_back(VGet(-1800.0f, 100.0f, -500.0f));
	positionList.push_back(VGet(-1800.0f, 100.0f, 500.0f));


	itr = positionList.begin();   //  �C�e���[�^��擪�ɐݒ�
}

void SecondStageMap::MapList2()
{
	positionList2.push_back(VGet(-5400.0f, 100.0f, 0.0f));
	positionList2.push_back(VGet(-4600.0f, 100.0f, 0.0f));

	itr2 = positionList2.begin();   //  �C�e���[�^��擪�ɐݒ�
}

void SecondStageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void SecondStageMap::Draw()
{
	MV1DrawModel(modelHandle);
}