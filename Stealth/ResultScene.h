#pragma once

#include "SceneBase.h"
#include <vector>
#include <string>

class Camera;
class FireWorksParticle;
class FadeManager;

using namespace std;

/// <summary>
/// ���U���g�V�[���N���X
/// </summary>
class ResultScene final : public SceneBase
{
public:

	ResultScene();
	virtual ~ResultScene();

	SceneType Update(float deltaTime)override;	//�X�V����
	void Draw()override;						//�`�揈��

private:
	ResultScene(const ResultScene&);	//�R�s�[�R���X�g���N�^
	
	void Initialize()override;				//����������
	void SceneChange();						//�V�[���؂�ւ�
	void Blink();							//�����̓_�ŏ���
	void BackGroundMove();					//�w�i�摜�̓���
	void ReturnScreen();					//��ʂ�J�ڂ���
	void InputScene(SceneType sceneType);	//�V�[�������

	string InputPath(string folderPath,	//�摜�̃p�X�����
					 string path);

	void EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle);		//�ԉ΃p�[�e�B�N����o�^
	void DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle);	//�ԉ΃p�[�e�B�N�����폜
	void FireWorksParticlePop();												//�ԉ΃p�[�e�B�N���̏o��

	Camera* camera;
	vector<FireWorksParticle*> fireWorksParticle;
	FadeManager* fadeManager;


	int fontHandle;			//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������
	int resultUiImage;		//���U���g��ʂ�UI�摜�i�[�p
	bool clear;
	int alpha;				//���ߓx
	int inc;
	int prevAlpha;
	bool titleFlag;			//�^�C�g����ʂ֑J�ڂ��邩���Ȃ���
	bool selectionFlag;		//�X�e�[�W�Z���N�V������ʂ֑J�ڂ��邩���Ȃ���
	int backGroundImage;	//���U���g��ʂ̔w�i�i�[�p
	int backGroundX;		//�w�i��X���W
	int backGroundY;		//�w�i��Y���W


	//�萔
	const string IMAGE_FOLDER_PATH;			//Image�t�H���_�܂ł̃p�X
	const string RESULT_UI_PATH;			//���U���g��ʂ�UI�̃p�X
	const string RESULT_BACKGROUND_PATH;	//���U���g��ʂ̔w�i�摜�̃p�X
	const int    PARTICLE_NUMBER;			//�p�[�e�B�N���̐�
};