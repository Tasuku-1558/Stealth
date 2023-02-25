#pragma once

#include "SceneBase.h"
#include <string>

using namespace std;

class FadeManager;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	 virtual ~TitleScene();

	void Initialize()override;					//����������
	void Activate()override;					//����������
	void Update(float deltaTime)override;		//�X�V����
	void Draw()override;						//�`�揈��

private:

	TitleScene(const TitleScene&);		//�R�s�[�R���X�g���N�^

	string InputPath(string folderPath,	//�摜�̃p�X�����
					 string path);

	void Blink();						//�����̓_�ŏ���
	void Finalize()override;			//�I������

	int backGroundHandle;				//�^�C�g������̊i�[�p
	int titleName;						//�^�C�g�����̉摜�i�[�p
	int titleUi;						//�X�e�[�W�I���V�[���֑J�ڃL�[��UI�i�[�p
	int alpha;							//���ߓx
	int inc;
	float frame;						//�t���[����

	FadeManager* fadeManager;			//�t�F�[�h�}�l�[�W���[�N���X�̃|�C���^

	//�萔
	const string VIDEO_FOLDER_PATH;	//video�t�H���_�܂ł̃p�X
	const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	const string PLAY_VIDEO_PATH;	//�^�C�g������̃p�X
	const string TITLENAME_PATH;	//�^�C�g�����̉摜�̃p�X
	const string TITLE_UI_PATH;		//�X�e�[�W�I���V�[���֑J�ڃL�[��UI�̃p�X

	//SceneBase* retScene = this;

};