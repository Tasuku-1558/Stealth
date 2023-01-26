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
	void Activate();
	void Finalize();								//�I������
	void Draw();									//�`�揈��
	void Stage1_Draw();								//�X�e�[�W1��UI�`�揈��
	void Stage2_Draw();								//�X�e�[�W2��UI�`�揈��

private:
	SelectionUi(const SelectionUi&);				//�R�s�[�R���X�g���N�^
	void MapInput(int number, ModelManager::ModelType modelType, VECTOR mapPos, VECTOR size, VECTOR rotate);	//�}�b�v������


	int selectionKeyImage;							//�X�e�[�W�Z���N�V����UI�摜
	int stageDescription[2];						//�X�e�[�W�̐����摜�n���h��
	int modelHandle[2];								//�}�b�v���f���n���h��
	VECTOR position[2];								//�}�b�v���f���̈ʒu


	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;			//image�t�H���_�܂ł̃p�X
	static const string SELECTION_KEY_PATH;			//�X�e�[�W�Z���N�V����UI�摜�̃p�X
	static const string STAGE1_DESCRIPTION_PATH;	//�X�e�[�W1�̐����摜�̃p�X
	static const string STAGE2_DESCRIPTION_PATH;	//�X�e�[�W2�̐����摜�̃p�X
	static const int	STAGE_NUMBER;				//�X�e�[�W��

	static const VECTOR STAGE1_POSITION;			//�X�e�[�W1���f���̈ʒu
	static const VECTOR STAGE1_SIZE;				//�X�e�[�W1���f���̔{��
	static const VECTOR STAGE1_ROTATE;				//�X�e�[�W1���f���̉�]�l

	static const VECTOR STAGE2_POSITION;			//�X�e�[�W2���f���̈ʒu
	static const VECTOR STAGE2_SIZE;				//�X�e�[�W2���f���̔{��
	static const VECTOR STAGE2_ROTATE;				//�X�e�[�W2���f���̉�]�l

};