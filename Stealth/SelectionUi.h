#pragma once

#include "DxLib.h"
#include "ModelManager.h"
#include <string>

using namespace std;

/// <summary>
/// �X�e�[�W�I����ʗpUI�N���X
/// </summary>
class SelectionUi final
{
public:

	SelectionUi();
	virtual ~SelectionUi();

	void Draw();									//�`�揈��
	void StageUiDraw(int mapNumber, int enemyNumber, 
					 int cakeNumber);				//�X�e�[�W��UI�`�揈��

	void TitleUiDraw();								//�^�C�g���֑J�ڂ���UI�`�揈��

private:
	SelectionUi(const SelectionUi&);				//�R�s�[�R���X�g���N�^

	void Initialize();								//����������
	void Finalize();								//�I������

	void MapInput(int number, ModelManager::ModelType modelType, 
				  VECTOR mapPos, VECTOR size, VECTOR rotate);		//�}�b�v������

	string InputPath(string folderPath,				//�摜�̃p�X�����
					 string imagePath);

	int fontHandle;										//�Q�[���t�H���g
	int selectionKeyImage;							//�X�e�[�W�Z���N�V����UI�摜
	int selectionUiImage;							//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�UI�摜
	int stageDescription;							//�X�e�[�W�̐����摜�n���h��
	int operationMethod;							//������@�����摜�̃n���h��
	int modelHandle[5];								//�}�b�v���f���n���h��
	VECTOR position[5];								//�}�b�v���f���̈ʒu

	//�萔
	const string IMAGE_FOLDER_PATH;			//image�t�H���_�܂ł̃p�X
	const string SELECTION_KEY_PATH;		//�X�e�[�W�Z���N�V����UI�摜�̃p�X
	const string SELECTION_TITLE_PATH;		//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�UI�摜
	const string STAGE_DESCRIPTION_PATH;	//�X�e�[�W�̐����摜�̃p�X
	const string OPERATION_METHOD_PATH;		//������@�����摜�̃p�X
	const int	 STAGE_NUMBER;				//�X�e�[�W��

	const VECTOR STAGE1_POSITION;			//�X�e�[�W1���f���̈ʒu
	const VECTOR STAGE1_SIZE;				//�X�e�[�W1���f���̔{��
	const VECTOR STAGE1_ROTATE;				//�X�e�[�W1���f���̉�]�l

	const VECTOR STAGE2_POSITION;			//�X�e�[�W2���f���̈ʒu
	const VECTOR STAGE2_SIZE;				//�X�e�[�W2���f���̔{��
	const VECTOR STAGE2_ROTATE;				//�X�e�[�W2���f���̉�]�l

	const VECTOR STAGE3_POSITION;			//�X�e�[�W3���f���̈ʒu
	const VECTOR STAGE3_SIZE;				//�X�e�[�W3���f���̔{��
	const VECTOR STAGE3_ROTATE;				//�X�e�[�W3���f���̉�]�l

	const VECTOR STAGE4_POSITION;			//�X�e�[�W4���f���̈ʒu
	const VECTOR STAGE4_SIZE;				//�X�e�[�W4���f���̔{��
	const VECTOR STAGE4_ROTATE;				//�X�e�[�W4���f���̉�]�l

	const VECTOR STAGE5_POSITION;			//�X�e�[�W5���f���̈ʒu
	const VECTOR STAGE5_SIZE;				//�X�e�[�W5���f���̔{��
	const VECTOR STAGE5_ROTATE;				//�X�e�[�W5���f���̉�]�l

};