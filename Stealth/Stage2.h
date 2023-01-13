#pragma once

#include "SceneBase.h"
#include <vector>

class Player;
class Enemy;
class Camera;
class Light;
class BackGround;
class Ball;
class Wall;
class HitChecker;
class Stage2Map;
class UiManager;
class FadeManager;


/// <summary>
/// �X�e�[�W�Q�N���X
/// </summary>
class Stage2 final : public SceneBase
{
public:
	 Stage2(SceneManager* const sceneManager);
	~Stage2();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	//�Q�[�����
	enum State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		GOAL,	//�S�[��
	};

private:
	Stage2(const Stage2&);		//�R�s�[�R���X�g���N�^

	Player* player;
	std::vector<Enemy*> enemy;
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Ball* ball;
	Ball* ball2;
	Wall* wall;
	Wall* wall2;
	Wall* wall3;
	HitChecker* hitChecker;
	Stage2Map* stage2Map;
	UiManager* uiManager;
	FadeManager* fadeManager;


	void EntryEnemy(Enemy* newEnemy);				//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);			//�G�l�~�[���폜
	void EnemyPop();								//�G�l�~�[�̏o��
	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void UpdateGoal(float deltaTime);				//�S�[��
	void (Stage2::* pUpdate)(float deltaTime);		//Update�֐��|�C���^

	State state;		//�Q�[�����
	int font;			//�Q�[���t�H���g
	bool pop;
};