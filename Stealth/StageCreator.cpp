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
	//ケーキのパーティクルオブジェクトから検索して削除
	auto iter = std::find(stage.begin(), stage.end(), deleteStage);

	if (iter != stage.end())
	{
		//ケーキのパーティクルオブジェクトを最後尾に移動してデータを消す
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