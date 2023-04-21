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

	void EntryStage(Stage* newStage);								//�G�l�~�[��o�^
	void DeleteStage(Stage* deleteStage);							//�G�l�~�[���폜
	void StagePop();												//�G�l�~�[�̏o��


	std::vector<Stage*> stage;

};