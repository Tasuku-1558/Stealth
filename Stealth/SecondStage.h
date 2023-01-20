#pragma once

#include "SceneBase.h"
#include "PreCompiledHeader.h"
#include <vector>

class Player;
class Enemy;
class Camera;
class Light;
class BackGround;
class BallBullet;
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
	enum class State
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
	std::vector<BallBullet*> ballBullet;
	std::vector<Wall*> wall;
	/*Wall* wall;
	Wall* wall2;
	Wall* wall3;*/
	HitChecker* hitChecker;
	SecondStageMap* secondStageMap;
	SecondStageMap* secondStageMap2;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void EntryEnemy(Enemy* newEnemy);				//エネミーを登録
	void DeleteEnemy(Enemy* deleteEnemy);			//エネミーを削除
	void EnemyPop();								//エネミーの出現

	void EntryBallBullet(BallBullet* newBallBullet);
	void DeleteBallBullet(BallBullet* deleteBallBullet);
	void BallBulletPop();

	void EntryWall(Wall* newWall);
	void DeleteWall(Wall* deleteWall);
	void WallPop();

	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateGoal(float deltaTime);				//ゴール
	void (SecondStage::* pUpdate)(float deltaTime);		//Update関数ポインタ

	State state;		//ゲーム状態
	int font;			//ゲームフォント
	bool enemyPop;		//エネミーの出現フラグ
	bool ballPop;		//ボールの出現フラグ
	bool wallPop;
	int count;
};