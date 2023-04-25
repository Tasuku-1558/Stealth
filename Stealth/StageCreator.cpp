#include "StageCreator.h"
#include "Stage.h"


char stage1[16][16] =
{
	1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
};

StageCreator::StageCreator()
	: STAGE_POS_Y(0.0f)
{
	StagePop(stage1);
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

void StageCreator::StagePop(char stageNumber[BLOCK_NUM_Z][BLOCK_NUM_X])
{
	for (int i = 0; i < BLOCK_NUM_Z; i++)
	{
		for (int j = 0; j < BLOCK_NUM_X; j++)
		{
			float posX = (j * 300.0f) + 50.0f;
			float posZ = (i * 300.0f) + 50.0f;

			if (stageNumber[j][i] == 0)
			{
				Stage* newStage = new Stage({ posX, STAGE_POS_Y, posZ });
				EntryStage(newStage);
			}
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