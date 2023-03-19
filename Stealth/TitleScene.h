#pragma once

#include "SceneBase.h"
#include "DxLib.h"
#include <string>

using namespace std;

class Light;
class Camera;
class FadeManager;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene final : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	SceneType Update(float deltaTime);		//�X�V����
	void Draw();							//�`�揈��

private:

	TitleScene(const TitleScene&);		//�R�s�[�R���X�g���N�^

	void Initialize();					//����������
	void Activate();					//����������
	void Blink();						//�����̓_�ŏ���
	void ChangeState();					//�^�C�g���̏�Ԃ̕ύX

	string InputPath(string folderPath,	//�摜�̃p�X�����
					 string path);

	//�^�C�g���̏��
	enum class TitleState
	{
		START,	//�Q�[�����n�߂�
		EXIT,	//�Q�[�����I������
	};

	TitleState titleState;				//�^�C�g���̏��
	int titleMovie;						//�^�C�g������̊i�[�p
	int titleName;						//�^�C�g�����̉摜�i�[�p
	int titleUi;						//�X�e�[�W�I���V�[���֑J�ڃL�[��UI�i�[�p
	int alpha;							//���ߓx
	int inc;
	float frame;						//�t���[����
	VECTOR spherePosition;				//3D���̂̈ʒu

	Light* light;
	Camera* camera;						//�J�����N���X�̃|�C���^
	FadeManager* fadeManager;			//�t�F�[�h�}�l�[�W���[�N���X�̃|�C���^


	//�萔
	const string VIDEO_FOLDER_PATH;	//video�t�H���_�܂ł̃p�X
	const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	const string PLAY_VIDEO_PATH;	//�^�C�g������̃p�X
	const string TITLENAME_PATH;	//�^�C�g�����̉摜�̃p�X
	const string TITLE_UI_PATH;		//�X�e�[�W�I���V�[���֑J�ڃL�[��UI�̃p�X
	const float  START_SPHERE_POSY;	//�X�^�[�g��Ԃ̋���Y���W
	const float  EXIT_SPHERE_POSY;	//�I����Ԃ̋���Y���W

};