#include "Stage.h"
#include "ModelManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">�ǃ��f���̈ʒu</param>
Stage::Stage(VECTOR position)
{
	//�ǃ��f���̓ǂݍ��݂ƈʒu��ݒ�
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE));
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �`�揈��
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(modelHandle);
}