#include "ThirdStageMap.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR ThirdStageMap::SIZE	 = { 50.0f, 50.0f, 55.0f };						//���f���̔{��
const VECTOR ThirdStageMap::POSITION = { -2600.0f, -100.0f, 2650.0f };				//���f���̈ʒu
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
	Finalize();
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
}

/// <summary>
/// �G�̍s���p�^�[�����X�g(�㉺�Ɉړ�����G)
/// </summary>
void ThirdStageMap::MapList()
{
	positionList.push_back({ -2500.0f, 0.0f, 800.0f });
	positionList.push_back({ -1500.0f, 0.0f, 800.0f });

	itr = positionList.begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g2(�S�[���̈ʒu���ǂ��G)
/// </summary>
void ThirdStageMap::MapList2()
{
	positionList2.push_back({ -2500.0f, 0.0f,  5000.0f });
	positionList2.push_back({ -2500.0f, 0.0f,  4300.0f });
	positionList2.push_back({ -2800.0f, 0.0f,  4300.0f });
	positionList2.push_back({ -2500.0f, 0.0f,  4300.0f });

	itr2 = positionList2.begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �`�揈��
/// </summary>
void ThirdStageMap::Draw()
{
	MV1DrawModel(modelHandle);
}