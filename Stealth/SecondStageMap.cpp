#include "SecondStageMap.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR SecondStageMap::SIZE	  = { 80.0f, 60.0f, 80.0f };				//���f���̔{��
const VECTOR SecondStageMap::POSITION = { -7000.0f, -100.0f, -2900.0f };		//���f���̈ʒu

using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SecondStageMap::SecondStageMap() : StageBase()
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SecondStageMap::~SecondStageMap()
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
void SecondStageMap::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE2));
	MV1SetScale(modelHandle, SIZE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [STAGE2]\n");
	}

	MapList();
	MapList2();
}

/// <summary>
/// �I������
/// </summary>
void SecondStageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// �G�̍s���p�^�[�����X�g(�ǂ̎�������G)
/// </summary>
void SecondStageMap::MapList()
{
	positionList.push_back({ -2200.0f, 0.0f, 600.0f });
	positionList.push_back({ -2200.0f, 0.0f, -700.0f });
	positionList.push_back({ -1400.0f, 0.0f, -700.0f });
	positionList.push_back({ -1400.0f, 0.0f, 600.0f });

	itr = positionList.begin();		//�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g2(�㉺�ړ��̓G)
/// </summary>
void SecondStageMap::MapList2()
{
	positionList2.push_back({ -5000.0f, 0.0f, 0.0f });
	positionList2.push_back({ -4400.0f, 0.0f, 0.0f });

	itr2 = positionList2.begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �`�揈��
/// </summary>
void SecondStageMap::Draw()
{
	MV1DrawModel(modelHandle);
}