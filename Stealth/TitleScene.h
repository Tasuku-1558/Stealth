#pragma once

#include "SceneBase.h"
#include <string>

using namespace std;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	~TitleScene();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

private:

	TitleScene(const TitleScene&);		//�R�s�[�R���X�g���N�^

	void Blink();						//�����̓_��

	int backGroundHandle;				//�^�C�g������̊i�[�p
	int titleName;						//�^�C�g�����̉摜�i�[�p
	int titleUi;						//�v���C�V�[���֑J�ڃL�[��UI�i�[�p
	int alpha;
	int inc;

	//�ÓI�萔
	static const string VIDEO_FOLDER_PATH;	//video�t�H���_�܂ł̃p�X
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string PLAY_VIDEO_PATH;	//�^�C�g������̃p�X
	static const string TITLENAME_PATH;		//�^�C�g�����̉摜�̃p�X
	static const string TITLE_UI_PATH;		//�v���C�V�[���֑J�ڃL�[��UI�̃p�X

};