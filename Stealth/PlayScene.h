#pragma once

#include "SceneBase.h"

class Player;
class Camera;

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
	Camera* camera;

	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void (PlayScene::* pUpdate)(float deltaTime);

	State state;		//ゲーム状態
};