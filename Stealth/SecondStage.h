#pragma once

#include "SceneBase.h"
#include <vector>


class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class CakeBullet;
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
		OVER,	//�Q�[���I�[�o�[
	};

private:
	SecondStage(const SecondStage&);		//�R�s�[�R���X�g���N�^
	
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	std::vector<Enemy*> enemy;
	std::vector<CakeBullet*> cakeBullet;
	HitChecker* hitChecker;
	SecondStageMap* secondStageMap;
	std::vector<CakeParticle*> cakeParticle;
	CakeRepopEffect* cakeEffect;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void EntryEnemy(Enemy* newEnemy);						//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);					//�G�l�~�[���폜
	void EnemyPop();										//�G�l�~�[�̏o��

	void EntryCakeBullet(CakeBullet* newCakeBullet);		//�P�[�L�o���b�g��o�^
	void DeleteCakeBullet(CakeBullet* deleteCakeBullet);	//�P�[�L�o���b�g���폜
	void CakeBulletPop();									//�P�[�L�o���b�g�̏o��

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//�P�[�L�̃p�[�e�B�N����o�^
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//�P�[�L�̃p�[�e�B�N�����폜
	void CakeParticlePop();											//�P�[�L�̃p�[�e�B�N���̏o��

	void UpdateStart(float deltaTime);						//�Q�[���J�n�O
	void UpdateGame(float deltaTime);						//�Q�[����
	void UpdateGoal(float deltaTime);						//�S�[��
	void UpdateOver(float deltaTime);						//�Q�[���I�[�o�[
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