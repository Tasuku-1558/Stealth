#pragma once

#include "DxLib.h"
#include "ModelManager.h"
#include <string>

using namespace std;

/// <summary>
/// �X�e�[�W�I����ʗpUi�N���X
/// </summary>
class SelectionUi final
{
public:
	SelectionUi();
	virtual ~SelectionUi();

	void Draw();		//�`�揈��
	void StageUiDraw(int mapNumber, int enemyNumber, 
					 int cakeNumber);		//�X�e�[�W��Ui�`�揈��

	void TitleUiDraw();		//�^�C�g���֑J�ڂ���Ui�`�揈��

private:
	SelectionUi(const SelectionUi&);	//�R�s�[�R���X�g���N�^

	void Initialize();			//����������
	void Finalize();			//�I������

	void MapInput(int number, ModelManager::ModelType modelType, 
				  VECTOR mapPos, VECTOR size, VECTOR rotate);		//�}�b�v������

	int fontHandle;				//�Q�[���t�H���g
	int selectionKeyImage;		//�X�e�[�W�Z���N�V����Ui�摜
	int selectionUiImage;		//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�Ui�摜
	int stageDescription;		//�X�e�[�W�̐����摜�n���h��
	int operationMethod;		//������@�����摜�̃n���h��
	int modelHandle[2];			//�}�b�v���f���n���h��
	VECTOR position[2];			//�}�b�v���f���̈ʒu

	//�萔
	const int	 SELECTION_FONT_SIZE;		//�Q�[���t�H���g�̃T�C�Y
	const int	 FONT_THICK;				//�t�H���g�̑���
	const int	 STAGE_NUMBER;				//�X�e�[�W��

	const VECTOR STAGE1_POSITION;			//�X�e�[�W1���f���̈ʒu
	const VECTOR STAGE1_SIZE;				//�X�e�[�W1���f���̔{��
	const VECTOR STAGE1_ROTATE;				//�X�e�[�W1���f���̉�]�l

	const VECTOR STAGE2_POSITION;			//�X�e�[�W2���f���̈ʒu
	const VECTOR STAGE2_SIZE;				//�X�e�[�W2���f���̔{��
	const VECTOR STAGE2_ROTATE;				//�X�e�[�W2���f���̉�]�l

	const string IMAGE_FOLDER_PATH;			//Image�t�H���_�܂ł̃p�X
	const string SELECTION_KEY_PATH;		//�X�e�[�W�Z���N�V����Ui�摜�̃p�X
	const string SELECTION_TITLE_PATH;		//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�Ui�摜
	const string STAGE_DESCRIPTION_PATH;	//�X�e�[�W�̐����摜�̃p�X
	const string OPERATION_METHOD_PATH;		//������@�����摜�̃p�X
};