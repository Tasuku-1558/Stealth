#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class StageMap;
class Player;
class Enemy;
class MonitoringEnemy;
class CakeBullet;
class GoalFlag;
class HitChecker;
class CakeRepopEffect;
class CakeParticle;
class UiManager;
class FadeManager;

/// <summary>
/// FourthStage�N���X
/// </summary>
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
	FourthStage(const FourthStage&);	//�R�s�[�R���X�g���N�^

	Camera* camera;
	Light* light;
	BackGround* backGround;
	StageMap* stageMap;
	Player* player;
	std::vector<Enemy*> enemy;
	MonitoringEnemy* monitoringEnemy;
	CakeBullet* cakeBullet;
	GoalFlag* goalFlag;
	HitChecker* hitChecker;
	CakeRepopEffect* cakeEffect;
	std::vector<CakeParticle*> cakeParticle;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void EntryEnemy(Enemy* newEnemy);								//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);							//�G�l�~�[���폜
	void EnemyPop();												//�G�l�~�[�̏o��

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//�P�[�L�̃p�[�e�B�N����o�^
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//�P�[�L�̃p�[�e�B�N�����폜
	void CakeParticlePop();											//�P�[�L�̃p�[�e�B�N���̏o��

	void UpdateStart(float deltaTime);						//�Q�[���J�n�O
	void UpdateGame(float deltaTime);						//�Q�[����
	void UpdateGoal(float deltaTime);						//�S�[��
	void UpdateOver(float deltaTime);						//�Q�[���I�[�o�[
	void (FourthStage::* pUpdate)(float deltaTime);			//Update�֐��|�C���^


	State state;			//�Q�[���̏��
	int   font;				//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������
	bool clear;


	//�ÓI�萔
	static const int PARTICLE_NUMBER;		//�p�[�e�B�N���̐�

};