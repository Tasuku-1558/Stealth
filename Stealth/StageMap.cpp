#include "StageMap.h"


using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelType"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
/// <param name="position"></param>
StageMap::StageMap(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position) : StageBase()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	MV1SetScale(modelHandle, size);
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageMap::~StageMap()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void StageMap::Initialize()
{
	MapList();
	MapList2();
	MapList3();
	MapList4();
	MapList5();

}

/// <summary>
/// �I������
/// </summary>
void StageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �`�揈��
/// </summary>
void StageMap::Draw()
{
	MV1DrawModel(modelHandle);
}

/// <summary>
/// �G�̍s���p�^�[�����X�g(���E�ړ��̓G)
/// FirstStage�̓G
/// </summary>
void StageMap::MapList()
{
	positionList[0].push_back({-3200.0f, 0.0f, 1000.0f});
	positionList[0].push_back({-3200.0f, 0.0f, -1000.0f});

	itr[0] = positionList[0].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g2(�ǂ̎�������G)
/// SecondStage�̓G
/// </summary>
void StageMap::MapList2()
{
	positionList[1].push_back({-2200.0f, 0.0f, 600.0f});
	positionList[1].push_back({-2200.0f, 0.0f, -700.0f});
	positionList[1].push_back({-1400.0f, 0.0f, -700.0f});
	positionList[1].push_back({-1400.0f, 0.0f, 600.0f});

	itr[1] = positionList[1].begin();	//�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g3(�㉺�ړ��̓G)
/// SecondStage�̓G
/// </summary>
void StageMap::MapList3()
{
	positionList[2].push_back({-5000.0f, 0.0f, 0.0f});
	positionList[2].push_back({-4400.0f, 0.0f, 0.0f});

	itr[2] = positionList[2].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g4(�㉺�ړ��̓G)
/// ThirdStage�̓G
/// </summary>
void StageMap::MapList4()
{
	positionList[3].push_back({-2500.0f, 0.0f, 800.0f});
	positionList[3].push_back({-1500.0f, 0.0f, 800.0f});

	itr[3] = positionList[3].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g5(�S�[���̈ʒu���ǂ��G)
/// ThirdStage�̓G
/// </summary>
void StageMap::MapList5()
{
	positionList[4].push_back({-2500.0f, 0.0f,  5000.0f});
	positionList[4].push_back({-2500.0f, 0.0f,  4300.0f});
	positionList[4].push_back({-2800.0f, 0.0f,  4300.0f});
	positionList[4].push_back({-2500.0f, 0.0f,  4300.0f});

	itr[4] = positionList[4].begin();   //�C�e���[�^��擪�ɐݒ�
}