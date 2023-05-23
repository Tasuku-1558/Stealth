#include "StageBlock.h"
#include "ModelManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">�ǃ��f���̈ʒu</param>
/// <param name="scale">�ǃ��f���̑傫��</param>
StageBlock::StageBlock(VECTOR position, VECTOR scale)
{
	//�ǃ��f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE_BLOCK));

	//�傫���ƈʒu��ݒ�
	MV1SetScale(modelHandle, scale);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageBlock::~StageBlock()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void StageBlock::Update(float deltaTime)
{
	//�����Ȃ�
}

/// <summary>
/// �`�揈��
/// </summary>
void StageBlock::Draw()
{
	MV1DrawModel(modelHandle);
}