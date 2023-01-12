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
/// ステージ２クラス
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

	//ゲーム状態
	enum State
	{
		START,	//開始前
		GAME,	//ゲーム中
	};

private:
	Stage2(const Stage2&);		//コピーコンストラクタ

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

	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void (Stage2::* pUpdate)(float deltaTime);		//Update関数ポインタ

	State state;		//ゲーム状態
	int font;			//ゲームフォント
};