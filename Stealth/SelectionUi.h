#pragma once

#include <string>
#include <vector>
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "Stage.h"

using namespace std;

/// <summary>
/// �X�e�[�W�I����ʗpUi�N���X
/// </summary>
class SelectionUi final
{
public:
	SelectionUi();
	virtual ~SelectionUi();

	void Draw();						//�`�揈��

	void StageUiDraw(int stageNumber,
					 int enemyNumber,
					 int cakeNumber);	//�X�e�[�W��Ui�`�揈��

	void TitleUiDraw();					//�^�C�g���֑J�ڂ���Ui�`�揈��

private:
	SelectionUi(const SelectionUi&);	//�R�s�[�R���X�g���N�^

	Stage* stage;
	vector<Stage*> activeStage;

	void Initialize();			//����������
	void Finalize();			//�I������
	void StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X]);		//�X�e�[�W�̏o��

	struct Ui
	{
		string imagePath;		//Ui�摜�̃p�X
	};

	int fontHandle;				//�Q�[���t�H���g
	int selectionUiImage[4];	//�Z���N�V����Ui�摜�̊i�[�p
	VECTOR stagePos;			//�X�e�[�W�̍��W

	//�萔
	const int	 SELECTION_UI_NUMBER;		//�Z���N�V����Ui�摜�̐�
	const int	 SELECTION_FONT_SIZE;		//�Q�[���t�H���g�̃T�C�Y
	const int	 FONT_THICK;				//�t�H���g�̑���
	const int	 STAGE_NUMBER;				//�X�e�[�W��

	const float  STAGE_POS_Y;				//�X�e�[�W��Y���W

	const VECTOR STAGE_SIZE;				//�X�e�[�W�̃T�C�Y

	const string IMAGE_FOLDER_PATH;			//Image�t�H���_�܂ł̃p�X
	const string SELECTION_KEY_PATH;		//�X�e�[�W�Z���N�V����Ui�摜�̃p�X
	const string SELECTION_TITLE_PATH;		//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�Ui�摜
	const string STAGE_DESCRIPTION_PATH;	//�X�e�[�W�̐����摜�̃p�X
	const string OPERATION_METHOD_PATH;		//������@�����摜�̃p�X
};