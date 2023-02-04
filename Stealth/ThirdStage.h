#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class MonitoringEnemy;
class BallBullet;
class HitChecker;
class ThirdStageMap;
class CakeRepopEffect;
class UiManager;


/// <summary>
/// ThirdStageクラス
/// </summary>
class ThirdStage final : public SceneBase
{
public:
	ThirdStage(SceneManager* const sceneManager);
	virtual ~ThirdStage();

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
	ThirdStage(const ThirdStage&);	//コピーコンストラクタ


	void EntryBallBullet(BallBullet* newBallBullet);		//ボールバレットを登録
	void DeleteBallBullet(BallBullet* deleteBallBullet);	//ボールバレットを削除
	void BallBulletPop();									//ボールバレットの出現
	
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	std::vector<Enemy*> enemy;
	MonitoringEnemy* monitoringEnemy;
	std::vector<BallBullet*> ballBullet;
	HitChecker* hitChecker;
	ThirdStageMap* thirdStageMap;
	CakeRepopEffect* cakeEffect;
	UiManager* uiManager;


	void UpdateStart(float deltaTime);						//ゲーム開始前
	void UpdateGame(float deltaTime);						//ゲーム中
	void UpdateGoal(float deltaTime);						//ゴール
	void (ThirdStage::* pUpdate)(float deltaTime);			//Update関数ポインタ


	State state;		//ゲームの状態
	int  font;			//ゲームフォント

	//静的定数
	//static const int GOAL_POSITION_X;					//ゴールの位置


};