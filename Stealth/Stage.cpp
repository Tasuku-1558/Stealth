#include "Stage.h"
#include "ModelManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">�ǃ��f���̈ʒu</param>
/// <param name="scale">�ǃ��f���̑傫��</param>
Stage::Stage(VECTOR position, VECTOR scale)
{
	//�ǃ��f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE));

	//�傫���ƈʒu��ݒ�
	MV1SetScale(modelHandle, scale);
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