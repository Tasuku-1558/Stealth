#pragma once

#include "SceneBase.h"
#include <vector>


class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class CakeBullet;
class Wall;
class HitChecker;
class SecondStageMap;
class CakeParticle;
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
		OVER,	//ゲームオーバー
	};

private:
	SecondStage(const SecondStage&);		//コピーコンストラクタ
	
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	std::vector<Enemy*> enemy;
	std::vector<CakeBullet*> cakeBullet;
	HitChecker* hitChecker;
	SecondStageMap* secondStageMap;
	std::vector<CakeParticle*> cakeParticle;
	CakeRepopEffect* cakeEffect;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void EntryEnemy(Enemy* newEnemy);						//エネミーを登録
	void DeleteEnemy(Enemy* deleteEnemy);					//エネミーを削除
	void EnemyPop();										//エネミーの出現

	void EntryCakeBullet(CakeBullet* newCakeBullet);		//ケーキバレットを登録
	void DeleteCakeBullet(CakeBullet* deleteCakeBullet);	//ケーキバレットを削除
	void CakeBulletPop();									//ケーキバレットの出現

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//ケーキのパーティクルを登録
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//ケーキのパーティクルを削除
	void CakeParticlePop();											//ケーキのパーティクルの出現

	void UpdateStart(float deltaTime);						//ゲーム開始前
	void UpdateGame(float deltaTime);						//ゲーム中
	void UpdateGoal(float deltaTime);						//ゴール
	void UpdateOver(float deltaTime);						//ゲームオーバー
	void (SecondStage::* pUpdate)(float deltaTime);			//Update関数ポインタ

	State state;			//ゲームの状態
	int   font;				//ゲームフォント
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら

	//静的定数
	static const float GOAL_POSITION_X;				//ゴールの位置X座標
	static const int   PARTICLE_NUMBER;				//パーティクルの数

};