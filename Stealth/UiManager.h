#pragma once

#include <string>
#include "GameScene.h"

using namespace std;

/// <summary>
/// UI�Ǘ��N���X
/// </summary>
class UiManager final
{
public:
	UiManager();
	virtual ~UiManager();

	void Draw(GameScene::GameState gameState,
			  int playerCount, bool hitUi);	//�`�揈��

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
		GRAPHIC_AMOUNT,		//�摜�̐�
	};

	void Initialize();								//����������
	void Finalize();								//�I������
	void StartGameDraw(UiManager::Graphic graphic);	//�Q�[���J�nUI
	void PlayerHpDraw(int playerCount);				//�v���C���[HPUI
	void OperationMethodDraw(bool hitUi);			//������@����UI

	int uiHandle[GRAPHIC_AMOUNT];					//�摜�n���h���i�[�p
	int alpha;										//���ߓx
	int inc;

	//�萔
	const int	 MAX_ALPHA;					//�ő哧�ߓx
	const string IMAGE_FOLDER_PATH;			//�摜�i�[�t�H���_
	const string UI_GRAPHIC_PATH;			//UI�摜
	const string IMAGE_FILENAME_EXTENSION;	//�摜�g���q
};