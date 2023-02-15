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
class HitChecker;
class CakeRepopEffect;
class CakeParticle;
class UiManager;
class FadeManager;

/// <summary>
/// FifthStage�N���X
/// </summary>
class FifthStage final : public SceneBase
{
public:
	FifthStage(SceneManager* const sceneManager);
	virtual ~FifthStage();

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
	FifthStage(const FifthStage&);	//�R�s�[�R���X�g���N�^

	Camera* camera;
	Light* light;
	BackGround* backGround;
	StageMap* stageMap;
	Player* player;
	std::vector<Enemy*> enemy;
	std::vector<MonitoringEnemy*> monitoringEnemy;
	CakeBullet* cakeBullet;
	HitChecker* hitChecker;
	CakeRepopEffect* cakeEffect;
	std::vector<CakeParticle*> cakeParticle;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void EntryEnemy(Enemy* newEnemy);								//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);							//�G�l�~�[���폜
	void EnemyPop();												//�G�l�~�[�̏o��

	void EntryMonitoringEnemy(MonitoringEnemy* newMonitoringEnemy);			//�Ď��G�l�~�[��o�^
	void DeleteMonitoringEnemy(MonitoringEnemy* deleteMonitoringEnemy);		//�Ď��G�l�~�[���폜
	void MonitoringEnemyPop();												//�Ď��G�l�~�[�̏o��

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//�P�[�L�̃p�[�e�B�N����o�^
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//�P�[�L�̃p�[�e�B�N�����폜
	void CakeParticlePop();											//�P�[�L�̃p�[�e�B�N���̏o��

	void UpdateStart(float deltaTime);						//�Q�[���J�n�O
	void UpdateGame(float deltaTime);						//�Q�[����
	void UpdateGoal(float deltaTime);						//�S�[��
	void UpdateOver(float deltaTime);						//�Q�[���I�[�o�[
	void (FifthStage::* pUpdate)(float deltaTime);			//Update�֐��|�C���^


	State state;			//�Q�[���̏��
	int   font;				//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������
	bool clear;


	//�ÓI�萔
	static const float GOAL_POSITION_X;				//�S�[���̈ʒuX���W
	static const float GOAL_POSITION_Z;				//�S�[���̈ʒuZ���W
	static const int   PARTICLE_NUMBER;				//�p�[�e�B�N���̐�

};