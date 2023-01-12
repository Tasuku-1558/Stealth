#include "Stage2Map.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR Stage2Map::SIZE	 = { 80.0f, 50.0f, 80.0f };					//���f���̔{��
const VECTOR Stage2Map::POSITION = { -200.0f, 50.0f, 1350.0f };				//���f���̈ʒu

using namespace std;

Stage2Map::Stage2Map() : ObjectBase()
{
	//�����Ȃ�
}

Stage2Map::~Stage2Map()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Stage2Map::Initialize()
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
}

void Stage2Map::MapList()
{
	positionList.push_back(VGet(-3200.0f, 100.0f, 1400.0f));
	positionList.push_back(VGet(-3200.0f, 100.0f, -1300.0f));

	itr = positionList.begin();   //  �C�e���[�^��擪�ɐݒ�
}

void Stage2Map::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Stage2Map::Draw()
{
	MV1DrawModel(modelHandle);
}