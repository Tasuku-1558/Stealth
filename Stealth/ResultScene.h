#pragma once

#include "SceneBase.h"
#include <vector>
#include <string>


class BackGround;
class FireWorksParticle;
class FadeManager;

using namespace std;


/// <summary>
/// ���U���g�V�[��
/// </summary>
class ResultScene final : public SceneBase
{
public:

	ResultScene(SceneManager* const sceneManager);
	virtual ~ResultScene();

	void Initialize();					//����������
	void Activate();					//����������
	void Update(float deltaTime);		//�X�V����
	void Draw();						//�`�揈��

private:
	ResultScene(const ResultScene&);	//�R�s�[�R���X�g���N�^
	
	void Finalize();					//�I������
	void SceneChange();					//�V�[���؂�ւ�
	void Blink();						//�����̓_�ŏ���
	void ReturnTitle(float deltaTime);				//�^�C�g����ʂ�
	void ReturnSelection(float deltaTime);			//�Z���N�V������ʂ�

	string InputPath(string folderPath,	//�摜�̃p�X�����
					 string path);

	void EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle);		//�ԉ΃p�[�e�B�N����o�^
	void DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle);	//�ԉ΃p�[�e�B�N�����폜
	void FireWorksParticlePop();												//�ԉ΃p�[�e�B�N���̏o��

	
	//void (ResultScene::* pUpdate)(float deltaTime);	//Update�֐��|�C���^


	BackGround* backGround;
	vector<FireWorksParticle*> fireWorksParticle;
	FadeManager* fadeManager;



	int font;				//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������
	int resultUiImage;
	int stageNo;
	bool clear;
	int alpha;
	int inc;
	int prevAlpha;
	bool title;
	bool selection;

	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string RESULT_UI_PATH;		//���U���g��ʂ�UI�̃p�X

};