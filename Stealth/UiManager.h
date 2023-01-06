#pragma once

#include <string>

#include "DxLib.h"
#include "PlayScene.h"


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

	void Draw(PlayScene::State state);


private:
	UiManager(const UiManager&);		//�R�s�[�R���X�g���N�^

	void StartGameDraw();				//�Q�[���J�nUI


	//�摜�̎��
	enum Graphic
	{
		STARGE1,
		GRAPHIC_AMOUNT
	};

	int count;
	int uiHandle[GRAPHIC_AMOUNT];		//�摜�n���h��


	//�ÓI�萔
	static const std::string FOLDER_PATH;			//�摜�i�[�t�H���_
	static const std::string UI_GRAPHIC_PATH;		//UI�摜
	static const std::string FILENAME_EXTENSION;	//�摜�g���q
};