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
	};

private:
	Stage2(const Stage2&);		//�R�s�[�R���X�g���N�^

	Player* player;
	Enemy* enemy;
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Ball* ball;
	Wall* wall;
	HitChecker* hitChecker;
	Stage2Map* stage2Map;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void (Stage2::* pUpdate)(float deltaTime);		//Update�֐��|�C���^

	State state;		//�Q�[�����
	int font;			//�Q�[���t�H���g
};