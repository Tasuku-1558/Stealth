#pragma once

#include "SceneBase.h"


class Player;
class Enemy;
class Camera;
class Light;
class Ball;
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
	 PlayScene();
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
	};

private:
	PlayScene(const PlayScene&);		//�R�s�[�R���X�g���N�^

	Player* player;
	Enemy* enemy;
	Camera* camera;
	Light* light;
	Ball* ball;
	HitChecker* hitChecker;
	Map* map;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void (PlayScene::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	State state;		//�Q�[�����
	int font;			//�Q�[���t�H���g

};