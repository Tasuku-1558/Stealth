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
class RepopEffect;
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

	void Initialize()override;				//����������
	void Finalize()override;				//�I������
	void Activate()override;				//����������
	void Update(float deltaTime)override;	//�X�V����
	void Draw()override;					//�`�揈��

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
	RepopEffect* cakeEffect;
	std::vector<CakeParticle*> cakeParticle;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void EntryEnemy(Enemy* newEnemy);								//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);							//�G�l�~�[���폜
	void EnemyPop();												//�G�l�~�[�̏o��

	//void EntryMonitoringEnemy(MonitoringEnemy* newMonitoringEnemy);			//�Ď��G�l�~�[��o�^
	//void DeleteMonitoringEnemy(MonitoringEnemy* deleteMonitoringEnemy);		//�Ď��G�l�~�[���폜
	//void MonitoringEnemyPop();												//�Ď��G�l�~�[�̏o��

	//void EntryCakeBullet(CakeBullet* newCakeBullet);		//�P�[�L�o���b�g��o�^
	//void DeleteCakeBullet(CakeBullet* deleteCakeBullet);	//�P�[�L�o���b�g���폜
	//void CakeBulletPop();									//�P�[�L�o���b�g�̏o��

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

	//�萔
	const int PARTICLE_NUMBER;			//�p�[�e�B�N���̐�

};