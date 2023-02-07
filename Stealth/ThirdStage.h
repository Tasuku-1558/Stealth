#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class MonitoringEnemy;
class BallBullet;
class HitChecker;
class ThirdStageMap;
class CakeRepopEffect;
class CakeParticle;
class UiManager;


/// <summary>
/// ThirdStage�N���X
/// </summary>
class ThirdStage final : public SceneBase
{
public:
	ThirdStage(SceneManager* const sceneManager);
	virtual ~ThirdStage();

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
	};

private:
	ThirdStage(const ThirdStage&);	//�R�s�[�R���X�g���N�^
	
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	std::vector<Enemy*> enemy;
	MonitoringEnemy* monitoringEnemy;
	std::vector<BallBullet*> ballBullet;
	HitChecker* hitChecker;
	ThirdStageMap* thirdStageMap;
	CakeRepopEffect* cakeEffect;
	std::vector<CakeParticle*> cakeParticle;
	UiManager* uiManager;

	void EntryEnemy(Enemy* newEnemy);								//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);							//�G�l�~�[���폜
	void EnemyPop();												//�G�l�~�[�̏o��

	void EntryBallBullet(BallBullet* newBallBullet);				//�{�[���o���b�g��o�^
	void DeleteBallBullet(BallBullet* deleteBallBullet);			//�{�[���o���b�g���폜
	void BallBulletPop();											//�{�[���o���b�g�̏o��

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//�P�[�L�̃p�[�e�B�N����o�^
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//�P�[�L�̃p�[�e�B�N�����폜
	void CakeParticlePop();											//�P�[�L�̃p�[�e�B�N���̏o��

	void UpdateStart(float deltaTime);						//�Q�[���J�n�O
	void UpdateGame(float deltaTime);						//�Q�[����
	void UpdateGoal(float deltaTime);						//�S�[��
	void (ThirdStage::* pUpdate)(float deltaTime);			//Update�֐��|�C���^


	State state;			//�Q�[���̏��
	int   font;				//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������


	//�ÓI�萔
	static const float GOAL_POSITION_X;				//�S�[���̈ʒuX���W
	static const float GOAL_POSITION_Z;				//�S�[���̈ʒuZ���W
	static const int   PARTICLE_NUMBER;				//�p�[�e�B�N���̐�


};