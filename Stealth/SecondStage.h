#pragma once

#include "SceneBase.h"
#include <vector>


class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class BallBullet;
class Wall;
class HitChecker;
class SecondStageMap;
class CakeRepopEffect;
class UiManager;
class FadeManager;


/// <summary>
/// SecondStageクラス
/// </summary>
class SecondStage final : public SceneBase
{
public:
	 SecondStage(SceneManager* const sceneManager);
	 virtual ~SecondStage();

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
	SecondStage(const SecondStage&);		//コピーコンストラクタ
	
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	std::vector<Enemy*> enemy;
	std::vector<BallBullet*> ballBullet;
	std::vector<Wall*> wall;
	HitChecker* hitChecker;
	SecondStageMap* secondStageMap;
	CakeRepopEffect* cakeEffect;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void EntryEnemy(Enemy* newEnemy);						//エネミーを登録
	void DeleteEnemy(Enemy* deleteEnemy);					//エネミーを削除
	void EnemyPop();										//エネミーの出現

	void EntryBallBullet(BallBullet* newBallBullet);		//ボールバレットを登録
	void DeleteBallBullet(BallBullet* deleteBallBullet);	//ボールバレットを削除
	void BallBulletPop();									//ボールバレットの出現

	void EntryWall(Wall* newWall);							//壁を登録
	void DeleteWall(Wall* deleteWall);						//壁を削除
	void WallPop();											//壁の出現

	void UpdateStart(float deltaTime);						//ゲーム開始前
	void UpdateGame(float deltaTime);						//ゲーム中
	void UpdateGoal(float deltaTime);						//ゴール
	void (SecondStage::* pUpdate)(float deltaTime);			//Update関数ポインタ

	State state;		//ゲームの状態
	int  font;			//ゲームフォント
	bool enemyPop;		//エネミーの出現フラグ
	bool ballPop;		//ボールの出現フラグ
	bool wallPop;		//壁の出現フラグ
	int frame;

	//静的定数
	static const int GOAL_POSITION;					//ゴールの位置
};