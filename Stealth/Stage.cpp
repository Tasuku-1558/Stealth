#include "Stage.h"


char stage1[5][5] =
{
	1,1,1,1,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,0,0,0,1,
	1,1,1,1,1,
	/*0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,*/
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelType"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
/// <param name="position"></param>
Stage::Stage(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position)
	: stageModel(0)
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	MV1SetScale(modelHandle, size);
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, position);

	stageModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE));
	MV1SetScale(stageModel, VGet(0.5f,0.5f,0.5f));

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
	Finalize();
}

/// <summary>
/// �I������
/// </summary>
void Stage::Finalize()
{
	MV1DeleteModel(stageModel);
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �`�揈��
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(modelHandle);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//���ł͂Ȃ��Ƃ���͕`�悵�Ȃ�
			if (stage1[i][j] == 0) continue;

			//�ǃ��f���̈ʒu��ݒ�
			MV1SetPosition(stageModel, VGet(j * 0.0f, 0.0f, i * 0.0f));

			//�S���̕ǂ̏�Ԃŕ`�悷��t���[���ԍ���ύX����
			int FrameNo = 0;
			if (stage1[i][j + 1] == 0) FrameNo += 1;
			if (stage1[i][j - 1] == 0) FrameNo += 2;
			if (stage1[i + 1][j] == 0) FrameNo += 4;
			if (stage1[i - 1][j] == 0) FrameNo += 8;

			//����o�����ԍ��̃t���[����`�悷��
			MV1DrawFrame(stageModel, FrameNo);
		}
	}
}