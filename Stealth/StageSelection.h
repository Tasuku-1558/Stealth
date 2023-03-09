#pragma once

#include "SceneBase.h"

class Light;
class Camera;
class SelectionUi;
class FadeManager;


/// <summary>
/// ステージ選択画面クラス
/// </summary>
class StageSelection final : public SceneBase
{
public:
	StageSelection();
	virtual ~StageSelection();

	SceneType Update(float deltaTime)override;				//更新処理
	void Draw()override;									//描画処理

	const int GetStage() { return stageNo; }

private:
	StageSelection(const StageSelection&);			//コピーコンストラクタ

	void Initialize()override;						//初期化処理
	void Activate()override;						//活性化処理
	void Finalize()override;						//終了処理
	int stageIncrement(int stageNumber);			//選択ステージを1つ先に持っていく
	int stageDecrement(int stageNumber);			//選択ステージを1つ前に持っていく
	void StageCreator(int stageNumber);				//各シーンへ遷移
	void KeyMove(float deltaTime);					//キー操作

	Light* light;
	Camera* camera;
	SelectionUi* selectionUi;
	FadeManager* fadeManager;

	int font;										//ゲームフォント
	int stageMax;									//最大ステージ数
	int stageNo;									//ステージナンバー
	int changeTimeCount;							//ステージ遷移カウント
	float frame;									//フレーム数
	float pushCount;								//ステージ切り替えカウント
	bool changeScene;								//シーンを遷移させるか

	//定数
	const int	STAGE_NUMBER;						//ステージの数
	const int   MAX_TIME;							//マックスステージ遷移カウント
	const int   FIRST_STAGE_NUMBER;					//最初に表示されるステージ
	const float PUSH_INTERVAL;						//切り替えカウントのインターバル

};