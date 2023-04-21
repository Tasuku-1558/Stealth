#include "StageCreator.h"
#include "Stage.h"

StageCreator::StageCreator()
{
	StagePop();
}

StageCreator::~StageCreator()
{
}

void StageCreator::EntryStage(Stage* newStage)
{
	stage.emplace_back(newStage);
}

void StageCreator::DeleteStage(Stage* deleteStage)
{
	//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(stage.begin(), stage.end(), deleteStage);

	if (iter != stage.end())
	{
		//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, stage.end() - 1);
		stage.pop_back();

		return;
	}
}

void StageCreator::StagePop()
{
}

void StageCreator::Update()
{
}

void StageCreator::Draw()
{
	for (auto stagePtr : stage)
	{
		stagePtr->Draw();
	}
}