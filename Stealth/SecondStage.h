#pragma once

#include "SceneBase.h"
#include "PreCompiledHeader.h"
#include <vector>

class Player;
class Enemy;
class Camera;
class Light;
class BackGround;
class BallBullet;
class Wall;
class HitChecker;
class SecondStageMap;
class UiManager;
class FadeManager;


/// <summary>
/// �Z�J���h�X�e�[�W�N���X
/// </summary>
class SecondStage final : public SceneBase
{
public:
	 SecondStage(SceneManager* const sceneManager);
	~SecondStage();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	//�Q�[�����
	enum class State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		GOAL,	//�S�[��
	};

private:
	SecondStage(const SecondStage&);		//�R�s�[�R���X�g���N�^

	Player* player;
	std::vector<Enemy*> enemy;
	Camera* camera;
	Light* light;
	BackGround* backGround;
	std::vector<BallBullet*> ballBullet;
	std::vector<Wall*> wall;
	/*Wall* wall;
	Wall* wall2;
	Wall* wall3;*/
	HitChecker* hitChecker;
	SecondStageMap* secondStageMap;
	SecondStageMap* secondStageMap2;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void EntryEnemy(Enemy* newEnemy);				//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);			//�G�l�~�[���폜
	void EnemyPop();								//�G�l�~�[�̏o��

	void EntryBallBullet(BallBullet* newBallBullet);
	void DeleteBallBullet(BallBullet* deleteBallBullet);
	void BallBulletPop();

	void EntryWall(Wall* newWall);
	void DeleteWall(Wall* deleteWall);
	void WallPop();

	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void UpdateGoal(float deltaTime);				//�S�[��
	void (SecondStage::* pUpdate)(float deltaTime);		//Update�֐��|�C���^

	State state;		//�Q�[�����
	int font;			//�Q�[���t�H���g
	bool enemyPop;		//�G�l�~�[�̏o���t���O
	bool ballPop;		//�{�[���̏o���t���O
	bool wallPop;
	int count;
};