#pragma once

#include "SceneBase.h"
#include "DxLib.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class CakeBullet;
class HitChecker;
class StageMap;
class GoalFlag;
class CakeParticle;
class EffectManager;
class UiManager;
class FadeManager;


/// <summary>
/// FirstStageクラス
/// </summary>
class FirstStage final : public SceneBase
{
public:
	FirstStage();
	virtual ~FirstStage();

	SceneType Update(float deltaTime)override;	//更新処理
	void Draw()override;						//描画処理

	void stage(int num);


	//ゲームの状態
	enum class GameState
	{
		START,	//開始前
		GAME,	//ゲーム中
		GOAL,	//ゴール
		OVER,	//ゲームオーバー
	};

private:
	FirstStage(const FirstStage&);	//コピーコンストラクタ

	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	Enemy* enemy;
	std::vector<CakeBullet*> cakeBullet;
	HitChecker* hitChecker;
	StageMap* stageMap;
	GoalFlag* goalFlag;
	std::vector<CakeParticle*> cakeParticle;
	EffectManager* effectManager;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void Initialize()override;				//初期化処理

	void EntryEnemy(Enemy* newEnemy);								//エネミーを登録
	void DeleteEnemy(Enemy* deleteEnemy);							//エネミーを削除
	void EnemyPop();												//エネミーの出現

	void EntryCakeBullet(CakeBullet* newCakeBullet);				//ケーキバレットを登録
	void DeleteCakeBullet(CakeBullet* deleteCakeBullet);			//ケーキバレットを削除
	void CakeBulletPop();											//ケーキバレットの出現

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//ケーキのパーティクルを登録
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//ケーキのパーティクルを削除
	void CakeParticlePop();											//ケーキのパーティクルの出現

	//各状態に応じた更新処理
	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateGoal(float deltaTime);				//ゴール
	void UpdateOver(float deltaTime);				//ゲームオーバー
	void (FirstStage::* pUpdate)(float deltaTime);	//Update関数ポインタ


	GameState gameState;	//ゲームの状態
	int	  fontHandle;		//ゲームフォント
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら


	bool clear;
	int stageNo;

	//定数
	const int PARTICLE_NUMBER;			//パーティクルの数
	const int PLAYER_HP;				//プレイヤーのHP数

};