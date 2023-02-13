#pragma once

#include "SceneBase.h"
#include <vector>

class FourthStage final : public SceneBase
{
public:
	FourthStage(SceneManager* const sceneManager);
	virtual ~FourthStage();

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
	FourthStage(const FourthStage&);		//コピーコンストラクタ



	void UpdateStart(float deltaTime);				//ゲーム開始前
	void UpdateGame(float deltaTime);				//ゲーム中
	void UpdateGoal(float deltaTime);				//ゴール
	void UpdateOver(float deltaTime);				//ゲームオーバー
	void (FourthStage::* pUpdate)(float deltaTime);	//Update関数ポインタ

	State state;			//ゲーム状態
	int	  font;				//ゲームフォント
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら
};