#pragma once

#include "SceneBase.h"
#include "PreCompiledHeader.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Stage;
class Player;
class Enemy;
class CakeBullet;
class HitChecker;
class GoalFlag;
class CakeParticle;
class EffectManager;
class UiManager;
class FadeManager;


/// <summary>
/// �Q�[���V�[���N���X
/// </summary>
class GameScene final : public SceneBase
{
public:
	GameScene();
	virtual ~GameScene();

	SceneType Update(float deltaTime)override;	//�X�V����
	void Draw()override;						//�`�揈��

	//�Q�[���̏��
	enum class GameState
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		GOAL,	//�S�[��
		OVER,	//�Q�[���I�[�o�[
	};

private:
	GameScene(const GameScene&);	//�R�s�[�R���X�g���N�^

	Camera* camera;
	Light* light;
	BackGround* backGround;
	std::vector<Stage*> stage;
	Player* player;
	Enemy* enemy;
	std::vector<CakeBullet*> cakeBullet;
	HitChecker* hitChecker;
	GoalFlag* goalFlag;
	std::vector<CakeParticle*> cakeParticle;
	EffectManager* effectManager;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void Initialize()override;				//����������
	void InputScene(bool decision);			//�V�[�������
	void ChangeScreen();					//��ʂ�ς���

	void EntryStage(Stage* newStage);								//�X�e�[�W��o�^
	void DeleteStage(Stage* deleteStage);							//�X�e�[�W���폜
	void StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X]);		//�X�e�[�W�̏o��

	void EntryEnemy(Enemy* newEnemy);								//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);							//�G�l�~�[���폜
	void EnemyPop(int number);										//�G�l�~�[�̏o��

	void EntryCakeBullet(CakeBullet* newCakeBullet);				//�P�[�L�o���b�g��o�^
	void DeleteCakeBullet(CakeBullet* deleteCakeBullet);			//�P�[�L�o���b�g���폜
	void CakeBulletPop(int number);									//�P�[�L�o���b�g�̏o��

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//�P�[�L�̃p�[�e�B�N����o�^
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//�P�[�L�̃p�[�e�B�N�����폜
	void CakeParticlePop();											//�P�[�L�̃p�[�e�B�N���̏o��

	//�e��Ԃɉ������X�V����
	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void UpdateGoal(float deltaTime);				//�S�[��
	void UpdateOver(float deltaTime);				//�Q�[���I�[�o�[
	void (GameScene::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	struct StageList
	{
		int number;				//�X�e�[�W�̔ԍ�
		char name[7];			//�X�e�[�W�̖��O
	};

	GameState gameState;	//�Q�[���̏��
	int	gameFontHandle;		//�Q�[���t�H���g
	int stageNo;			//�I�������X�e�[�W�i�[�p
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������
	bool clear;				//�Q�[�����N���A�������ǂ���

	//�萔
	const int	FIRST_STAGE_NUMBER;		//�X�e�[�W1�̔ԍ�
	const int	SECOND_STAGE_NUMBER;	//�X�e�[�W2�̔ԍ�
	const int	GAME_FONT_SIZE;			//�Q�[���t�H���g�̃T�C�Y
	const int	FONT_THICK;				//�t�H���g�̑���
	const int	PARTICLE_NUMBER;		//�p�[�e�B�N���̐�
	const int	PLAYER_HP;				//�v���C���[��HP��
	const float GAME_START_COUNT;		//�Q�[���J�n�J�E���g
	const float MAX_PARTICLE_INTERVAL;	//�ő�p�[�e�B�N���o���̃C���^�\�o��
	const float PARTICLE_INTERVAL;		//�����̃p�[�e�B�N���o���C���^�[�o��
	const float STAGE_POS_Y;			//�X�e�[�W��Y���W

};