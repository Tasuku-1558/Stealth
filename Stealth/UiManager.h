#pragma once

#include <string>

#include "DxLib.h"
#include "FirstStage.h"
#include "SecondStage.h"


/// <summary>
/// UI�Ǘ��N���X
/// </summary>
class UiManager final
{
public:
	 UiManager();
	 virtual ~UiManager();

	void Initialize();		//����������
	void Activate();		//����������
	void Finalize();		//�I������

	void Draw(FirstStage::State state, int playerCount, bool hitUi);	//FirstStage�`�揈��
	void Draw(SecondStage::State state, int playerCount);				//SecondStage�`�揈��

	
private:
	UiManager(const UiManager&);			//�R�s�[�R���X�g���N�^

	void StartGameDraw();					//�Q�[���J�nUI
	void PlayerHpDraw(int playerCount);		//�v���C���[HPUI
	void OperationMethodDraw(bool hitUi);	//������@����UI


	//�摜�̎��
	enum Graphic
	{
		STAGE1,				//�X�e�[�W�P�X�^�[�g�摜
		PLAYER_HP,			//�v���C���[HP�摜
		PLAYER_HP_FRAME,	//�v���C���[HP�g�摜
		OPERATION,			//������@�����摜
		BALLOON,			//�����o���摜
		CLEAR,				//�Q�[���N���A�摜
		STAGE2,				//�X�e�[�W�Q�X�^�[�g�摜
		FRAME,				//�t���[���摜
		KEY,				//�v���C���[�ړ��L�[�摜
		GRAPHIC_AMOUNT		//�摜�̐�
	};

	int count;
	
	int uiHandle[GRAPHIC_AMOUNT];					//�摜�n���h��
	

	//�ÓI�萔
	static const std::string IMAGE_FOLDER_PATH;		//�摜�i�[�t�H���_
	static const std::string UI_GRAPHIC_PATH;		//UI�摜
	static const std::string FILENAME_EXTENSION;	//�摜�g���q
};