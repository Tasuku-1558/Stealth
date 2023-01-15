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
class SecondStageMap;
class UiManager;
class FadeManager;


/// <summary>
/// セカンドステージクラス
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

	//ゲーム状態
	enum State
	{
		START,	//開始前
		GAME,	//ゲーム中
		GOAL,	//ゴール
	};

private:
	SecondStage(const SecondStage&);		//コピーコンストラクタ

	Player* player;
	std::vector<Enemy*> enemy;
	Camera* camera;
	Light* light;
	BackGround* backGround;
	std::vector<Ball*> ball;
	Wall* wall;
	Wall* wall2;
	Wall* wall3;
	HitChecker* hitChecker;
	SecondStageMap* secondStageMap;
	SecondStageMap* secondStageMap2;
	UiManager* uiManager;
	FadeManager* fadeManager;


	void EntryEnemy(Enemy* newEnemy);				//エネミーを登録
	void DeleteEnemy(Enemy* deleteEnemy);			//エネミーを削除
	void EnemyPop();								//エネミーの出現
	void EntryBall(Ball* newBall);					//ボールを登録
	void DeleteBall(Ball* deleteBall);				//ボールを削除
	void BallPop();									//ボールの出現
	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateGoal(float deltaTime);				//ゴール
	void (SecondStage::* pUpdate)(float deltaTime);		//Update関数ポインタ

	State state;		//ゲーム状態
	int font;			//ゲームフォント
	bool enemyPop;		//エネミーの出現フラグ
	bool ballPop;		//ボールの出現フラグ
};