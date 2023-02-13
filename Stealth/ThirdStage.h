#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class StageMap;
class Player;
class Enemy;
class MonitoringEnemy;
class CakeBullet;
class HitChecker;
class CakeRepopEffect;
class CakeParticle;
class UiManager;
class FadeManager;

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
		OVER,	//ゲームオーバー
	};

private:
	ThirdStage(const ThirdStage&);	//コピーコンストラクタ
	
	Camera* camera;
	Light* light;
	BackGround* backGround;
	StageMap* stageMap;
	Player* player;
	std::vector<Enemy*> enemy;
	std::vector<MonitoringEnemy*> monitoringEnemy;
	std::vector<CakeBullet*> cakeBullet;
	HitChecker* hitChecker;
	CakeRepopEffect* cakeEffect;
	std::vector<CakeParticle*> cakeParticle;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void EntryEnemy(Enemy* newEnemy);								//エネミーを登録
	void DeleteEnemy(Enemy* deleteEnemy);							//エネミーを削除
	void EnemyPop();												//エネミーの出現

	void EntryMonitoringEnemy(MonitoringEnemy* newMonitoringEnemy);			//監視エネミーを登録
	void DeleteMonitoringEnemy(MonitoringEnemy* deleteMonitoringEnemy);		//監視エネミーを削除
	void MonitoringEnemyPop();												//監視エネミーの出現

	void EntryCakeBullet(CakeBullet* newCakeBullet);				//ケーキバレットを登録
	void DeleteCakeBullet(CakeBullet* deleteCakeBullet);			//ケーキバレットを削除
	void CakeBulletPop();											//ケーキバレットの出現

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//ケーキのパーティクルを登録
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//ケーキのパーティクルを削除
	void CakeParticlePop();											//ケーキのパーティクルの出現

	void UpdateStart(float deltaTime);						//ゲーム開始前
	void UpdateGame(float deltaTime);						//ゲーム中
	void UpdateGoal(float deltaTime);						//ゴール
	void UpdateOver(float deltaTime);						//ゲームオーバー
	void (ThirdStage::* pUpdate)(float deltaTime);			//Update関数ポインタ


	State state;			//ゲームの状態
	int   font;				//ゲームフォント
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら


	//静的定数
	static const float GOAL_POSITION_X;				//ゴールの位置X座標
	static const float GOAL_POSITION_Z;				//ゴールの位置Z座標
	static const int   PARTICLE_NUMBER;				//パーティクルの数


};