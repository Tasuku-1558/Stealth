#pragma once

#include "SceneBase.h"

class Player;
class Enemy;
class Camera;
class Light;
class BackGround;
class BallBullet;
class Wall;
class HitChecker;
class Map;
class Effect;
class UiManager;
class FadeManager;

/// <summary>
/// FirstStageクラス
/// </summary>
class FirstStage final : public SceneBase
{
public:
	 FirstStage(SceneManager* const sceneManager);
	 virtual ~FirstStage();

	void Initialize();				//初期化処理
	void Finalize();				//終了処理
	void Activate();				//活性化処理
	void Update(float deltaTime);	//更新処理
	void Draw();					//描画処理

	//ゲームの状態
	enum class State
	{
		START,	//開始前
		GAME,	//ゲーム中
		GOAL,	//ゴール
	};

private:
	FirstStage(const FirstStage&);	//コピーコンストラクタ

	Player* player;
	Enemy* enemy;
	Camera* camera;
	Light* light;
	BackGround* backGround;
	BallBullet* ballBullet;
	Wall* wall;
	HitChecker* hitChecker;
	Map* map;
	Effect* effect;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateGoal(float deltaTime);				//ゴール
	void (FirstStage::* pUpdate)(float deltaTime);	//Update関数ポインタ

	State state;		//ゲーム状態
	int font;			//ゲームフォント
	
};