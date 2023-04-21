#pragma once
#include <vector>

class Stage;

class StageCreator final
{
public:
	StageCreator();
	virtual ~StageCreator();

	void Update();
	void Draw();

private:

	void EntryStage(Stage* newStage);								//エネミーを登録
	void DeleteStage(Stage* deleteStage);							//エネミーを削除
	void StagePop();												//エネミーの出現


	std::vector<Stage*> stage;

};