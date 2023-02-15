#pragma once

#include "SceneBase.h"
#include <vector>

class FireWorksParticle;
class FadeManager;

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

	void EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle);		//�ԉ΃p�[�e�B�N����o�^
	void DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle);	//�ԉ΃p�[�e�B�N�����폜
	void FireWorksParticlePop();												//�ԉ΃p�[�e�B�N���̏o��

	void UpdateGame(float deltaTime);				//�Q�[����
	void ReturnTitle(float deltaTime);				//�^�C�g����ʂ�
	void ReturnSelection(float deltaTime);			//�Z���N�V������ʂ�
	void ReturnStage(float deltaTime);				//������x�v���C
	void (ResultScene::* pUpdate)(float deltaTime);	//Update�֐��|�C���^


	std::vector<FireWorksParticle*> fireWorksParticle;
	FadeManager* fadeManager;



	int font;				//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������

};