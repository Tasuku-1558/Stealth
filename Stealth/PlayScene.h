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
/// プレイシーンクラス
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

	//ゲーム状態
	enum State
	{
		START,	//開始前
		GAME,	//ゲーム中
		GOAL,	//ゴール
	};

private:
	PlayScene(const PlayScene&);		//コピーコンストラクタ

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

	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateGoal(float deltaTime);				//ゴール
	void (PlayScene::* pUpdate)(float deltaTime);	//Update関数ポインタ

	State state;		//ゲーム状態
	int font;			//ゲームフォント
};