#include "Wall.h"
#include "ModelManager.h"


const VECTOR Wall::SIZE		= { 2.0f, 2.0f, 2.0f };		//���f���̔{��
const VECTOR Wall::POSITION = { -2500.0f,30.0f,0.0f };	//���f���̈ʒu


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="WALL"></param>
Wall::Wall(Object WALL, VECTOR pos)
{
	position = pos;
}

Wall::~Wall()
{
	// �I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Wall::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::WALL));
	MV1SetScale(modelHandle, SIZE);

	MV1SetPosition(modelHandle, position);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [WALL]\n");
	}
}

void Wall::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Wall::Draw()
{
	MV1DrawModel(modelHandle);
}