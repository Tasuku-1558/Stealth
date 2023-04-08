#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class CakeBullet;
class HitChecker;
class Stage;
class GoalFlag;
class CakeParticle;
class EffectManager;
class UiManager;
class FadeManager;


/// <summary>
/// ゲームシーンクラス
/// </summary>
class GameScene final : public SceneBase
{
public:
	GameScene();
	virtual ~GameScene();

	SceneType Update(float deltaTime)override;	//更新処理
	void Draw()override;						//描画処理

	//ゲームの状態
	enum class GameState
	{
		START,	//開始前
		GAME,	//ゲーム中
		GOAL,	//ゴール
		OVER,	//ゲームオーバー
	};

private:
	GameScene(const GameScene&);	//コピーコンストラクタ

	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	Enemy* enemy;
	std::vector<CakeBullet*> cakeBullet;
	HitChecker* hitChecker;
	Stage* stage;
	GoalFlag* goalFlag;
	std::vector<CakeParticle*> cakeParticle;
	EffectManager* effectManager;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void Initialize()override;				//初期化処理
	void InputScene(bool decision);			//シーンを入力
	void ChangeScreen();					//画面を変える

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
	void (GameScene::* pUpdate)(float deltaTime);	//Update関数ポインタ


	GameState gameState;	//ゲームの状態
	int	  fontHandle;		//ゲームフォント
	int stageNo;			//選択したステージ格納用
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら
	bool clear;

	//定数
	const int	PARTICLE_NUMBER;		//パーティクルの数
	const int	PLAYER_HP;				//プレイヤーのHP数
	const float GAME_START_COUNT;		//ゲーム開始カウント
	const float MAX_PARTICLE_INTERVAL;	//最大パーティクル出現のインタ―バル

};