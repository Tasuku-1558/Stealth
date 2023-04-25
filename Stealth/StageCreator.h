#pragma once
#include <vector>
#include "PreCompiledHeader.h"

class Stage;

/// <summary>
/// �X�e�[�W�����N���X
/// </summary>
class StageCreator final
{
public:
	StageCreator();
	virtual ~StageCreator();

	void Draw();		//�`�揈��

private:
	StageCreator(const StageCreator&);		//�R�s�[�R���X�g���N�^

	void EntryStage(Stage* newStage);		//�X�e�[�W��o�^
	void DeleteStage(Stage* deleteStage);	//�X�e�[�W���폜
	void StagePop(char stageNumber[BLOCK_NUM_Z][BLOCK_NUM_X]);		//�X�e�[�W�̏o��

	std::vector<Stage*> stage;

	//�萔
	const float STAGE_POS_Y;	//�X�e�[�W��Y���W
};