#include "Map.h"
#include "Common.h"
#include "ModelManager.h"


const VECTOR Map::SIZE	   = { 30.0f, 10.0f, 30.0f };		//���f���̔{��
const VECTOR Map::POSITION = { -5000.0f, 0.0f, 500.0f };	//���f���̈ʒu

using namespace std;

Map::Map() : ObjectBase()
{
	//�����Ȃ�
}

Map::~Map()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Map::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE1));
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [STAGE]\n");
	}

	MapList();
	
}

void Map::MapList()
{
	positionList.push_back(VGet(-2700.0f, 100.0f, 1400.0f));
	positionList.push_back(VGet(-2700.0f, 100.0f, -1300.0f));

	itr = positionList.begin();   //  �C�e���[�^��擪�ɐݒ�
}

void Map::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Map::Activate()
{
}

void Map::Draw()
{
	MV1DrawModel(modelHandle);
}