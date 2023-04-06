#include "StageMap.h"

using namespace std;

char stage1[16][16] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
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
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelType"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
/// <param name="position"></param>
StageMap::StageMap(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position)
	: kabe(0)
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	MV1SetScale(modelHandle, size);
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, position);

	kabe = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::KABE));
	MV1SetPosition(kabe, position);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageMap::~StageMap()
{
	Finalize();
}

/// <summary>
/// �I������
/// </summary>
void StageMap::Finalize()
{
	MV1DeleteModel(kabe);
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �`�揈��
/// </summary>
void StageMap::Draw()
{
	MV1DrawModel(modelHandle);
	int i, j;

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			// ���ł͂Ȃ��Ƃ���͕`�悵�Ȃ�
			if (stage1[i][j] == 0) continue;

			// �ǃ��f���̍��W��ύX����
			MV1SetPosition(kabe, VGet(j * 1000.0f, 0.0f, i * 1000.0f));

			// �S���̕ǂ̏�Ԃŕ`�悷��t���[���ԍ���ύX����
			int FrameNo = 0;
			if (stage1[i][j + 1] == 0) FrameNo += 1;
			if (stage1[i][j - 1] == 0) FrameNo += 2;
			if (stage1[i + 1][j] == 0) FrameNo += 4;
			if (stage1[i - 1][j] == 0) FrameNo += 8;

			// ����o�����ԍ��̃t���[����`�悷��
			MV1DrawFrame(kabe, FrameNo);
		}
	}
}