#pragma once

#include "SceneBase.h"

class Camera;
class Light;
class BackGround;
class Stage;
class Player;
class Enemy;
class CakeBullet;
class HitChecker;
class GoalFlag;
class EffectManager;
class UiManager;
class FadeManager;
class Set;

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
	Stage* stage;
	Player* player;
	Enemy* enemy;
	CakeBullet* cakeBullet;
	HitChecker* hitChecker;
	GoalFlag* goalFlag;
	EffectManager* effectManager;
	UiManager* uiManager;
	FadeManager* fadeManager;

	vector<CakeBullet*> activeCakeBullet;
	vector<Stage*> activeStage;
	vector<Enemy*> activeEnemy;

	vector<VECTOR> cakeBulletPosition;
	vector<VECTOR> enemyPosition;


	void Initialize()override;				//初期化処理
	void InputScene(bool decision);			//シーンを入力
	void ChangeScreen();					//画面を変える

	void CakeBulletPop(int number, int cakeNumber);					//ケーキバレットの出現
	void EnemyPop(int number, char stageName[7], int enemyNumber);	//エネミーの出現
	void StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X]);		//ステージの出現

	//各状態に応じた更新処理
	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateGoal(float deltaTime);				//ゴール
	void UpdateOver(float deltaTime);				//ゲームオーバー
	void (GameScene::* pUpdate)(float deltaTime);	//Update関数ポインタ

	struct StageList
	{
		int number;			//ステージの番号
		char name[7];		//ステージの名前
		int cakeNumber;		//ケーキの数
		int enemyNumber;	//エネミーの数
	};

	GameState gameState;	//ゲームの状態
	int	gameFontHandle;		//ゲームフォント
	int stageNo;			//選択したステージ格納用
	float gameStartCount;	//ゲーム開始カウント
	bool clear;				//ゲームをクリアしたかどうか

	//定数
	const int	MAX_STAGE_NUMBER;		//最大ステージ数
	const int	FIRST_STAGE_NUMBER;		//ステージ1の番号
	const int	SECOND_STAGE_NUMBER;	//ステージ2の番号
	const int	GAME_FONT_SIZE;			//ゲームフォントのサイズ
	const int	FONT_THICK;				//フォントの太さ
	const int	PLAYER_HP;				//プレイヤーのHP数
	const float MAX_GAME_START_COUNT;	//最大ゲーム開始カウント
	const float STAGE_POS_Y;			//ステージのY座標
};