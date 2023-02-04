#include "FirstStageMap.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR FirstStageMap::SIZE	   = { 80.0f, 50.0f, 80.0f };						//���f���̔{��
const VECTOR FirstStageMap::POSITION   = { -2700.0f, -100.0f, -750.0f };				//���f���̈ʒu
const VECTOR FirstStageMap::ROTATE     = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };		//���f���̉�]�l

using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
FirstStageMap::FirstStageMap() : StageBase()
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FirstStageMap::~FirstStageMap()
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
void FirstStageMap::Initialize()
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
void FirstStageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// �G�̍s���p�^�[�����X�g
/// ���E�ړ��̓G
/// </summary>
void FirstStageMap::MapList()
{
	positionList.push_back(VGet(-3200.0f, 100.0f, 1000.0f));
	positionList.push_back(VGet(-3200.0f, 100.0f, -1000.0f));

	itr = positionList.begin();   //  �C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �`�揈��
/// </summary>
void FirstStageMap::Draw()
{
	MV1DrawModel(modelHandle);
}