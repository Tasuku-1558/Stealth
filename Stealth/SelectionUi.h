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
	void StageUiDraw(int number);					//�X�e�[�W��UI�`�揈��
	void TitleUiDraw();								//�^�C�g���֑J�ڂ���UI�`�揈��

private:
	SelectionUi(const SelectionUi&);				//�R�s�[�R���X�g���N�^

	void Finalize();								//�I������

	void MapInput(int number, ModelManager::ModelType modelType, 
				  VECTOR mapPos, VECTOR size, VECTOR rotate);		//�}�b�v������

	std::string InputPath(std::string folderPath,	//�摜�̃p�X�����
						  std::string path);


	int selectionKeyImage;							//�X�e�[�W�Z���N�V����UI�摜
	int selectionUiImage;							//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�UI�摜
	int stageDescription[4];						//�X�e�[�W�̐����摜�n���h��
	int modelHandle[4];								//�}�b�v���f���n���h��
	VECTOR position[4];								//�}�b�v���f���̈ʒu
	


	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;			//image�t�H���_�܂ł̃p�X
	static const string SELECTION_KEY_PATH;			//�X�e�[�W�Z���N�V����UI�摜�̃p�X
	static const string SELECTION_TITLE_PATH;		//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�UI�摜
	static const string STAGE1_DESCRIPTION_PATH;	//�X�e�[�W1�̐����摜�̃p�X
	static const string STAGE2_DESCRIPTION_PATH;	//�X�e�[�W2�̐����摜�̃p�X
	static const string STAGE3_DESCRIPTION_PATH;	//�X�e�[�W3�̐����摜�̃p�X
	static const string STAGE4_DESCRIPTION_PATH;	//�X�e�[�W4�̐����摜�̃p�X
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

};