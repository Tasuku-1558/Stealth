#include "Map.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR Map::SIZE	   = { 80.0f, 50.0f, 80.0f };						//���f���̔{��
const VECTOR Map::POSITION = { -2700.0f, -100.0f, -750.0f };				//���f���̈ʒu
const VECTOR Map::ROTATE   = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };		//���f���̉�]�l

using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map() : StageBase()
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void Map::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE1));
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [STAGE1]\n");
	}

	MapList();
}

/// <summary>
/// �I������
/// </summary>
void Map::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// �G�̍s���p�^�[�����X�g
/// </summary>
void Map::MapList()
{
	positionList.push_back(VGet(-3200.0f, 100.0f, 1400.0f));
	positionList.push_back(VGet(-3200.0f, 100.0f, -1300.0f));

	itr = positionList.begin();   //  �C�e���[�^��擪�ɐݒ�
}

void Map::MiniMap()
{
	/*pDotX = x + int(pGloX * exRate);
	pDotY = y + int(pGloY * exRate);*/

	DrawRotaGraph(x, y, exRate, 0, mapGraph, false);
	DrawBoxAA(mapFlameX, mapFlameY, mapFlameX + miniMapWidth, mapFlameY + miniMapHeight, GetColor(0, 0, 0), false, 3);
	DrawBoxAA(pDotX - int(SCREEN_WIDTH * exRate / 2), pDotY - int(SCREEN_HEIGHT * exRate / 2), pDotX + int(SCREEN_WIDTH * exRate / 2), pDotY + int(SCREEN_HEIGHT * exRate / 2), GetColor(255, 0, 0), false, 2);
	DrawCircle(pDotX, pDotY + 12, dotSize, GetColor(0, 0, 0), true);
}

/// <summary>
/// �`�揈��
/// </summary>
void Map::Draw()
{
	MV1DrawModel(modelHandle);

	//MiniMap();
}