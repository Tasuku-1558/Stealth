#include "Wall.h"
#include "ModelManager.h"


const VECTOR Wall::SIZE		= { 2.0f, 2.0f, 2.0f };		//���f���̔{��
const VECTOR Wall::POSITION = { -2500.0f,30.0f,0.0f };	//���f���̈ʒu


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
Wall::Wall(VECTOR pos)
{
	position = pos;
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wall::~Wall()
{
	// �I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
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

/// <summary>
/// �I������
/// </summary>
void Wall::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// �`�揈��
/// </summary>
void Wall::Draw()
{
	MV1DrawModel(modelHandle);
}