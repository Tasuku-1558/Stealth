#pragma once

#include "SceneBase.h"

class Camera;
class Light;
class BackGround;
class Stage;
class Player;
class Enemy;
class CakeBullet;
class HitChecker;
class GoalFlag;
class EffectManager;
class UiManager;
class FadeManager;
class Set;

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
	Stage* stage;
	Player* player;
	Enemy* enemy;
	CakeBullet* cakeBullet;
	HitChecker* hitChecker;
	GoalFlag* goalFlag;
	EffectManager* effectManager;
	UiManager* uiManager;
	FadeManager* fadeManager;

	vector<CakeBullet*> activeCakeBullet;
	vector<Stage*> activeStage;
	vector<Enemy*> activeEnemy;

	vector<VECTOR> cakeBulletPosition;
	vector<VECTOR> enemyPosition;


	void Initialize()override;				//����������
	void InputScene(bool decision);			//�V�[�������
	void ChangeScreen();					//��ʂ�ς���

	void CakeBulletPop(int number, int cakeNumber);					//�P�[�L�o���b�g�̏o��
	void EnemyPop(int number, char stageName[7], int enemyNumber);	//�G�l�~�[�̏o��
	void StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X]);		//�X�e�[�W�̏o��

	//�e��Ԃɉ������X�V����
	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void UpdateGoal(float deltaTime);				//�S�[��
	void UpdateOver(float deltaTime);				//�Q�[���I�[�o�[
	void (GameScene::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	struct StageList
	{
		int number;			//�X�e�[�W�̔ԍ�
		char name[7];		//�X�e�[�W�̖��O
		int cakeNumber;		//�P�[�L�̐�
		int enemyNumber;	//�G�l�~�[�̐�
	};

	GameState gameState;	//�Q�[���̏��
	int	gameFontHandle;		//�Q�[���t�H���g
	int stageNo;			//�I�������X�e�[�W�i�[�p
	float gameStartCount;	//�Q�[���J�n�J�E���g
	bool clear;				//�Q�[�����N���A�������ǂ���

	//�萔
	const int	MAX_STAGE_NUMBER;		//�ő�X�e�[�W��
	const int	FIRST_STAGE_NUMBER;		//�X�e�[�W1�̔ԍ�
	const int	SECOND_STAGE_NUMBER;	//�X�e�[�W2�̔ԍ�
	const int	GAME_FONT_SIZE;			//�Q�[���t�H���g�̃T�C�Y
	const int	FONT_THICK;				//�t�H���g�̑���
	const int	PLAYER_HP;				//�v���C���[��HP��
	const float MAX_GAME_START_COUNT;	//�ő�Q�[���J�n�J�E���g
	const float STAGE_POS_Y;			//�X�e�[�W��Y���W
};