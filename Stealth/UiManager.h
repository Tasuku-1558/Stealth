#pragma once

#include <string>

#include "DxLib.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "FourthStage.h"
#include "FifthStage.h"


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

	void Draw(FirstStage::State state,
			  int playerCount, bool hitUi);	//FirstStage��UI�`�揈��

	void Draw(SecondStage::State state, 
			  int playerCount);				//SecondStage��UI�`�揈��

	void Draw(ThirdStage::State state,
			  int playerCount);				//ThirdStage�̕`�揈��

	void Draw(FourthStage::State state,
			  int playerCount);				//FourthStage�̕`�揈��

	void Draw(FifthStage::State state,
		int playerCount);					//FifthStage�̕`�揈��

	void CakeGetDraw(bool cakeGet);			//�P�[�L�������Ă��邩��UI

private:
	UiManager(const UiManager&);			//�R�s�[�R���X�g���N�^

	//�摜�̎��
	enum Graphic
	{
		STAGE1,				//�X�e�[�W1�X�^�[�g�摜
		PLAYER_HP,			//�v���C���[HP�摜
		PLAYER_HP_FRAME,	//�v���C���[HP�g�摜
		OPERATION,			//������@�����摜
		BALLOON,			//�����o���摜
		CLEAR,				//�Q�[���N���A�摜
		STAGE2,				//�X�e�[�W2�X�^�[�g�摜
		FRAME,				//�v���C���[HP�t���[���摜
		CAKE,				//�P�[�L�摜
		STAGE3,				//�X�e�[�W3�X�^�[�g�摜
		STAGE4,				//�X�e�[�W4�X�^�[�g�摜
		STAGE5,				//�X�e�[�W5�X�^�[�g�摜
		GRAPHIC_AMOUNT		//�摜�̐�
	};

	void StartGameDraw(UiManager::Graphic graphic);	//�Q�[���J�nUI
	void PlayerHpDraw(int playerCount);				//�v���C���[HPUI
	void OperationMethodDraw(bool hitUi);			//������@����UI

	int stageCount;									//�X�e�[�W���̕\���J�E���g
	
	int uiHandle[GRAPHIC_AMOUNT];					//�摜�n���h��


	//�ÓI�萔
	static const std::string IMAGE_FOLDER_PATH;		//�摜�i�[�t�H���_
	static const std::string UI_GRAPHIC_PATH;		//UI�摜
	static const std::string FILENAME_EXTENSION;	//�摜�g���q
};