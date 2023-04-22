#include "StageCreator.h"
#include "Stage.h"


char stage1[16][16] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};


StageCreator::StageCreator()
{
	StagePop();
}

StageCreator::~StageCreator()
{
	for (auto stagePtr : stage)
	{
		DeleteStage(stagePtr);
	}
}

void StageCreator::EntryStage(Stage* newStage)
{
	stage.emplace_back(newStage);
}

void StageCreator::DeleteStage(Stage* deleteStage)
{
	//�X�e�[�W�I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(stage.begin(), stage.end(), deleteStage);

	if (iter != stage.end())
	{
		//�X�e�[�W�I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, stage.end() - 1);
		stage.pop_back();

		return;
	}
}

void StageCreator::StagePop()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			float x = (i * 300.0f) + 50.0f;
			float z = (j * 300.0f) + 50.0f;

			Stage* newStage = new Stage({ z, 0.0f, x });
			EntryStage(newStage);
		}
	}
}

void StageCreator::Draw()
{
	for (auto stagePtr : stage)
	{
		stagePtr->Draw();
	}
}