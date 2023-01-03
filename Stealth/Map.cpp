#include "Map.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR Map::SIZE	   = { 80.0f, 50.0f, 80.0f };		//���f���̔{��
const VECTOR Map::POSITION = { -2700.0f, 0.0f, -750.0f };	//���f���̈ʒu

using namespace Math3d;
using namespace std;

Map::Map() : ObjectBase()
	, collisionModel(0)
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
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [STAGE1]\n");
	}


	/*collisionModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE1));

	MV1SetScale(collisionModel, SIZE);
	MV1SetRotationXYZ(collisionModel, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	position = POSITION;

	MV1SetPosition(collisionModel, position + VGet(-45, 0, -35));

	MV1SetupCollInfo(collisionModel);*/

	MapList();
}

void Map::MapList()
{
	positionList.push_back(VGet(-3200.0f, 100.0f, 1400.0f));
	positionList.push_back(VGet(-3200.0f, 100.0f, -1300.0f));

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

	// �R���W�������f�������݂���ꍇ�͔������`��
	/*if (collisionModel != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		MV1DrawModel(collisionModel);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}*/
}