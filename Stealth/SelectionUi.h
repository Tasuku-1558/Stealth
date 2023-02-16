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

	void Initialize();								//����������
	void Activate();								//����������
	void Draw();									//�`�揈��
	void StageUiDraw(int mapNumber,
					 int enemyNumber, 
					 int cakeNumber);				//�X�e�[�W��UI�`�揈��

	void TitleUiDraw();								//�^�C�g���֑J�ڂ���UI�`�揈��

private:
	SelectionUi(const SelectionUi&);				//�R�s�[�R���X�g���N�^

	void Finalize();								//�I������

	void MapInput(int number, ModelManager::ModelType modelType, 
				  VECTOR mapPos, VECTOR size, VECTOR rotate);		//�}�b�v������

	string InputPath(string folderPath,		//�摜�̃p�X�����
					 string imagePath);

	int font;										//�Q�[���t�H���g
	int selectionKeyImage;							//�X�e�[�W�Z���N�V����UI�摜
	int selectionUiImage;							//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�UI�摜
	int stageDescription;							//�X�e�[�W�̐����摜�n���h��
	int operationMethod;							//������@�����摜�̃n���h��
	int modelHandle[5];								//�}�b�v���f���n���h��
	VECTOR position[5];								//�}�b�v���f���̈ʒu


	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;			//image�t�H���_�܂ł̃p�X
	static const string SELECTION_KEY_PATH;			//�X�e�[�W�Z���N�V����UI�摜�̃p�X
	static const string SELECTION_TITLE_PATH;		//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�UI�摜
	static const string STAGE_DESCRIPTION_PATH;		//�X�e�[�W�̐����摜�̃p�X
	static const string OPERATION_METHOD_PATH;		//������@�����摜�̃p�X
	static const int	STAGE_NUMBER;				//�X�e�[�W��

	static const VECTOR STAGE1_POSITION;			//�X�e�[�W1���f���̈ʒu
	static const VECTOR STAGE1_SIZE;				//�X�e�[�W1���f���̔{��
	static const VECTOR STAGE1_ROTATE;				//�X�e�[�W1���f���̉�]�l

	static const VECTOR STAGE2_POSITION;			//�X�e�[�W2���f���̈ʒu
	static const VECTOR STAGE2_SIZE;				//�X�e�[�W2���f���̔{��
	static const VECTOR STAGE2_ROTATE;				//�X�e�[�W2���f���̉�]�l

	static const VECTOR STAGE3_POSITION;			//�X�e�[�W3���f���̈ʒu
	static const VECTOR STAGE3_SIZE;				//�X�e�[�W3���f���̔{��
	static const VECTOR STAGE3_ROTATE;				//�X�e�[�W3���f���̉�]�l

	static const VECTOR STAGE4_POSITION;			//�X�e�[�W4���f���̈ʒu
	static const VECTOR STAGE4_SIZE;				//�X�e�[�W4���f���̔{��
	static const VECTOR STAGE4_ROTATE;				//�X�e�[�W4���f���̉�]�l

	static const VECTOR STAGE5_POSITION;			//�X�e�[�W5���f���̈ʒu
	static const VECTOR STAGE5_SIZE;				//�X�e�[�W5���f���̔{��
	static const VECTOR STAGE5_ROTATE;				//�X�e�[�W5���f���̉�]�l

};