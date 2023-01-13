#pragma once

#include <string>

#include "DxLib.h"
#include "PlayScene.h"
#include "Stage2.h"

class Enemy;
class HitChecker;

/// <summary>
/// UI�Ǘ��N���X
/// </summary>
class UiManager final
{
public:
	 UiManager();
	~UiManager();

	void Initialize();
	void Finalize();

	void Draw(PlayScene::State state, Enemy* enemy, HitChecker* hitChecker);
	void Draw(Stage2::State state, Enemy* enemy);

private:
	UiManager(const UiManager&);		//�R�s�[�R���X�g���N�^

	void StartGameDraw();				//�Q�[���J�nUI
	void PlayerHpDraw(Enemy* enemy);	//�v���C���[HPUI
	void OperationMethodDraw(HitChecker* hitChecker);	//������@����UI


	//�摜�̎��
	enum Graphic
	{
		STARGE1,
		PLAYER_HP,			//�v���C���[HP�摜
		PLAYER_HP_FRAME,	//�v���C���[HP�g�摜
		OPERATION,			//������@�����摜
		BALLOON,			//�����o���摜
		CREAR,				//�Q�[���N���A�摜
		STAGE2,
		FRAME,				//�t���[���摜
		GRAPHIC_AMOUNT		//�摜�̐�
	};

	int count;
	int uiHandle[GRAPHIC_AMOUNT];		//�摜�n���h��


	//�ÓI�萔
	static const std::string FOLDER_PATH;			//�摜�i�[�t�H���_
	static const std::string UI_GRAPHIC_PATH;		//UI�摜
	static const std::string FILENAME_EXTENSION;	//�摜�g���q
};