#pragma once

#include "SceneBase.h"
#include <vector>


class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class BallBullet;
class Wall;
class HitChecker;
class SecondStageMap;
class CakeParticle;
class CakeRepopEffect;
class UiManager;
class FadeManager;


/// <summary>
/// SecondStage�N���X
/// </summary>
class SecondStage final : public SceneBase
{
public:
	 SecondStage(SceneManager* const sceneManager);
	 virtual ~SecondStage();

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
	SecondStage(const SecondStage&);		//�R�s�[�R���X�g���N�^
	
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	std::vector<Enemy*> enemy;
	std::vector<BallBullet*> ballBullet;
	HitChecker* hitChecker;
	SecondStageMap* secondStageMap;
	std::vector<CakeParticle*> cakeParticle;
	CakeRepopEffect* cakeEffect;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void EntryEnemy(Enemy* newEnemy);						//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);					//�G�l�~�[���폜
	void EnemyPop();										//�G�l�~�[�̏o��

	void EntryBallBullet(BallBullet* newBallBullet);		//�{�[���o���b�g��o�^
	void DeleteBallBullet(BallBullet* deleteBallBullet);	//�{�[���o���b�g���폜
	void BallBulletPop();									//�{�[���o���b�g�̏o��

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//�P�[�L�̃p�[�e�B�N����o�^
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//�P�[�L�̃p�[�e�B�N�����폜
	void CakeParticlePop();											//�P�[�L�̃p�[�e�B�N���̏o��

	void UpdateStart(float deltaTime);						//�Q�[���J�n�O
	void UpdateGame(float deltaTime);						//�Q�[����
	void UpdateGoal(float deltaTime);						//�S�[��
	void (SecondStage::* pUpdate)(float deltaTime);			//Update�֐��|�C���^

	State state;			//�Q�[���̏��
	int   font;				//�Q�[���t�H���g
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������

	//�ÓI�萔
	static const float GOAL_POSITION_X;				//�S�[���̈ʒuX���W
	static const int   PARTICLE_NUMBER;				//�p�[�e�B�N���̐�

};