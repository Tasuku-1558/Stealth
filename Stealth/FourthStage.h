#pragma once

#include "SceneBase.h"
#include <vector>

class FourthStage final : public SceneBase
{
public:
	FourthStage(SceneManager* const sceneManager);
	virtual ~FourthStage();

	void Initialize();				//����������
	void Finalize();				//�I������
	void Activate();				//����������
	void Update(float deltaTime);	//�X�V����
	void Draw();					//�`�揈��

	//�Q�[���̏��
	enum class State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		GOAL,	//�S�[��
		OVER,	//�Q�[���I�[�o�[
	};

private:
	FourthStage(const FourthStage&);		//�R�s�[�R���X�g���N�^



	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void UpdateGoal(float deltaTime);				//�S�[��
	void UpdateOver(float deltaTime);				//�Q�[���I�[�o�[
	void (FourthStage::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	State state;			//�Q�[�����
	int	  font;				//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������
};