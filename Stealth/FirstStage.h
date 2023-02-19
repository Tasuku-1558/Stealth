#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class CakeBullet;
class HitChecker;
class StageMap;
class GoalFlag;
class CakeRepopEffect;
class CakeParticle;
class UiManager;
class FadeManager;

/// <summary>
/// FirstStage�N���X
/// </summary>
class FirstStage final : public SceneBase
{
public:
	 FirstStage(SceneManager* const sceneManager);
	 virtual ~FirstStage();

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
	FirstStage(const FirstStage&);	//�R�s�[�R���X�g���N�^

	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	Enemy* enemy;
	CakeBullet* cakeBullet;
	HitChecker* hitChecker;
	StageMap* stageMap;
	GoalFlag* goalFlag;
	CakeRepopEffect* cakeEffect;
	std::vector<CakeParticle*> cakeParticle;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//�P�[�L�̃p�[�e�B�N����o�^
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//�P�[�L�̃p�[�e�B�N�����폜
	void CakeParticlePop();											//�P�[�L�̃p�[�e�B�N���̏o��

	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void UpdateGoal(float deltaTime);				//�S�[��
	void UpdateOver(float deltaTime);				//�Q�[���I�[�o�[
	void (FirstStage::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	State state;			//�Q�[�����
	int	  font;				//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������

	bool clear;
	int stageNo;

	//�ÓI�萔
	static const int PARTICLE_NUMBER;			//�p�[�e�B�N���̐�
};