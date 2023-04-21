#include "Stage.h"
#include "ModelManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelType"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
/// <param name="position"></param>
Stage::Stage(/*ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, */VECTOR position)
	: stageModel(0)
{
	/*modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	MV1SetScale(modelHandle, size);
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, position);*/

	stageModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE));

	//�ǃ��f���̈ʒu��ݒ�
	MV1SetPosition(stageModel, position);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(stageModel);

	//MV1DeleteModel(modelHandle);
}

/// <summary>
/// �`�揈��
/// </summary>
void Stage::Draw()
{
	//MV1DrawModel(modelHandle);

	MV1DrawModel(stageModel);
}