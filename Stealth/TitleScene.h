#pragma once

#include "SceneBase.h"
#include "DxLib.h"
#include <string>

class Light;
class Camera;
class FadeManager;

using namespace std;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene final : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	SceneType Update(float deltaTime)override;		//�X�V����
	void Draw()override;							//�`�揈��

private:

	TitleScene(const TitleScene&);		//�R�s�[�R���X�g���N�^

	void Initialize()override;			//����������
	void Blink();						//�����̓_�ŏ���
	void ChangeState();					//�^�C�g���̏�Ԃ̕ύX

	string InputPath(string folderPath,
					 string path);		//�摜�̃p�X�����

	//�^�C�g���̏��
	enum class TitleState
	{
		START,	//�Q�[�����n�߂�
		EXIT,	//�Q�[�����I������
	};

	TitleState titleState;				//�^�C�g���̏��
	int titleMovie;						//�^�C�g������̊i�[�p
	int titleName;						//�^�C�g�����̉摜�i�[�p
	int startUi;						//�Q�[�����n�߂�J�ڃL�[��UI�i�[�p
	int exitUi;							//�Q�[�����I������J�ڃL�[��UI�i�[�p
	int alpha;							//���ߓx
	int inc;
	float frame;						//�t���[����
	VECTOR spherePosition;				//3D���̂̈ʒu

	Light* light;						//���C�g�N���X�̃|�C���^
	Camera* camera;						//�J�����N���X�̃|�C���^
	FadeManager* fadeManager;			//�t�F�[�h�}�l�[�W���[�N���X�̃|�C���^


	//�萔
	const string VIDEO_FOLDER_PATH;	//Video�t�H���_�܂ł̃p�X
	const string IMAGE_FOLDER_PATH;	//Image�t�H���_�܂ł̃p�X
	const string PLAY_VIDEO_PATH;	//�^�C�g������̃p�X
	const string TITLENAME_PATH;	//�^�C�g�����̉摜�̃p�X
	const string START_UI_PATH;		//�Q�[�����n�߂�J�ڃL�[��UI�̃p�X
	const string EXIT_UI_PATH;		//�Q�[�����I������J�ڃL�[��UI�̃p�X
	const int	 MAX_ALPHA;			//�ő哧�ߓx
	const int	 PLAY_POSITION;		//�^�C�g������̍Đ��ʒu
	const float  START_SPHERE_POS_Z;//�X�^�[�g��Ԃ̋���Z���W
	const float  EXIT_SPHERE_POS_Z;	//�I����Ԃ̋���Z���W

};