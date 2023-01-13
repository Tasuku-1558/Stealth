#pragma once

#include "SceneBase.h"


class Player;
class Enemy;
class Camera;
class Light;
class BackGround;
class Ball;
class Wall;
class HitChecker;
class Map;
class UiManager;
class FadeManager;

/// <summary>
/// �v���C�V�[���N���X
/// </summary>
class PlayScene final : public SceneBase
{
public:
	 PlayScene(SceneManager* const sceneManager);
	~PlayScene();

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
	PlayScene(const PlayScene&);		//�R�s�[�R���X�g���N�^

	Player* player;
	Enemy* enemy;
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Ball* ball;
	Wall* wall;
	HitChecker* hitChecker;
	Map* map;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void UpdateGoal(float deltaTime);				//�S�[��
	void (PlayScene::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	State state;		//�Q�[�����
	int font;			//�Q�[���t�H���g
};