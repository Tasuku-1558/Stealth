#pragma once

#include "SceneBase.h"
#include "PreCompiledHeader.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Stage;
class Player;
class Enemy;
class CakeBullet;
class HitChecker;
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
	std::vector<Stage*> stage;
	Player* player;
	Enemy* enemy;
	std::vector<CakeBullet*> cakeBullet;
	HitChecker* hitChecker;
	GoalFlag* goalFlag;
	std::vector<CakeParticle*> cakeParticle;
	EffectManager* effectManager;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void Initialize()override;				//初期化処理
	void InputScene(bool decision);			//シーンを入力
	void ChangeScreen();					//画面を変える

	void EntryStage(Stage* newStage);								//ステージを登録
	void DeleteStage(Stage* deleteStage);							//ステージを削除
	void StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X]);		//ステージの出現

	void EntryEnemy(Enemy* newEnemy);								//エネミーを登録
	void DeleteEnemy(Enemy* deleteEnemy);							//エネミーを削除
	void EnemyPop(int number);										//エネミーの出現

	void EntryCakeBullet(CakeBullet* newCakeBullet);				//ケーキバレットを登録
	void DeleteCakeBullet(CakeBullet* deleteCakeBullet);			//ケーキバレットを削除
	void CakeBulletPop(int number);									//ケーキバレットの出現

	void EntryCakeParticle(CakeParticle* newCakeParticle);			//ケーキのパーティクルを登録
	void DeleteCakeParticle(CakeParticle* deleteCakeParticle);		//ケーキのパーティクルを削除
	void CakeParticlePop();											//ケーキのパーティクルの出現

	//各状態に応じた更新処理
	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateGoal(float deltaTime);				//ゴール
	void UpdateOver(float deltaTime);				//ゲームオーバー
	void (GameScene::* pUpdate)(float deltaTime);	//Update関数ポインタ

	struct StageList
	{
		int number;				//ステージの番号
		char name[7];			//ステージの名前
	};

	GameState gameState;	//ゲームの状態
	int	gameFontHandle;		//ゲームフォント
	int stageNo;			//選択したステージ格納用
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら
	bool clear;				//ゲームをクリアしたかどうか

	//定数
	const int	FIRST_STAGE_NUMBER;		//ステージ1の番号
	const int	SECOND_STAGE_NUMBER;	//ステージ2の番号
	const int	GAME_FONT_SIZE;			//ゲームフォントのサイズ
	const int	FONT_THICK;				//フォントの太さ
	const int	PARTICLE_NUMBER;		//パーティクルの数
	const int	PLAYER_HP;				//プレイヤーのHP数
	const float GAME_START_COUNT;		//ゲーム開始カウント
	const float MAX_PARTICLE_INTERVAL;	//最大パーティクル出現のインタ―バル
	const float PARTICLE_INTERVAL;		//初期のパーティクル出現インターバル
	const float STAGE_POS_Y;			//ステージのY座標

};