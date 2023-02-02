#include "ThirdStageMap.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR ThirdStageMap::SIZE	 = { 80.0f, 50.0f, 80.0f };						//���f���̔{��
const VECTOR ThirdStageMap::POSITION = { -200.0f, -100.0f, 1350.0f };				//���f���̈ʒu
const VECTOR ThirdStageMap::ROTATE	 = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };	//���f���̉�]�l


using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ThirdStageMap::ThirdStageMap() : StageBase()
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ThirdStageMap::~ThirdStageMap()
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
void ThirdStageMap::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE3));
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [STAGE3]\n");
	}

	MapList();
	MapList2();
}

/// <summary>
/// �I������
/// </summary>
void ThirdStageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// �G�̍s���p�^�[�����X�g(�㉺�Ɉړ�����G)
/// </summary>
void ThirdStageMap::MapList()
{
}

/// <summary>
/// �G�̍s���p�^�[�����X�g2
/// </summary>
void ThirdStageMap::MapList2()
{
}

/// <summary>
/// �`�揈��
/// </summary>
void ThirdStageMap::Draw()
{
	MV1DrawModel(modelHandle);
}