#pragma once

#include "SceneBase.h"

class Player;
class Enemy;
class Camera;
class Light;
class Boal;
class HitChecker;

//プレイシーンクラス
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

	//ゲーム状態
	enum State
	{
		START,	//開始前
		GAME,	//ゲーム中
	};

private:
	PlayScene(const PlayScene&);		//コピーコンストラクタ

	Player* player;
	Enemy* enemy;
	Camera* camera;
	Light* light;
	Boal* boal;
	HitChecker* hitChecker;

	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void (PlayScene::* pUpdate)(float deltaTime);

	State state;		//ゲーム状態
	int font;
};