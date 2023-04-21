#pragma once
#include <vector>

class Stage;

/// <summary>
/// �X�e�[�W�����N���X
/// </summary>
class StageCreator final
{
public:
	StageCreator();
	virtual ~StageCreator();

	void Draw();

private:
	StageCreator(const StageCreator&);		//�R�s�[�R���X�g���N�^

	void EntryStage(Stage* newStage);		//�X�e�[�W��o�^
	void DeleteStage(Stage* deleteStage);	//�X�e�[�W���폜
	void StagePop();						//�X�e�[�W�̏o��


	std::vector<Stage*> stage;

};