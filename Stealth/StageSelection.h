#pragma once

#include "SceneBase.h"
#include "SceneManager.h"


class Light;
class SelectionUi;
class FadeManager;


/// <summary>
/// ステージ選択画面クラス
/// </summary>
class StageSelection final : public SceneBase
{
public:
	 StageSelection(SceneManager* const sceneManager);
	 virtual ~StageSelection();

	void Initialize();								//初期化処理
	void Finalize();								//終了処理
	void Activate();								//活性化処理
	void Update(float deltaTime);					//更新処理
	void Draw();									//描画処理


private:
	StageSelection(const StageSelection&);			//コピーコンストラクタ


	Light* light;
	SelectionUi* selectionUi;
	FadeManager* fadeManager;

	int StageCreator(int stageNumber);
	int stageDecrement(int stageNumber);			//選択ステージを1つ前に持っていく
	int stageIncrement(int stageNumber);			//選択ステージを1つ先に持っていく
	void KeyMove(float deltaTime);					//キー操作

	
	int font;										//ゲームフォント
	int stageMax;									//最大ステージ数
	int stageNo;									//ステージナンバー
	bool changeScene;								//シーンを遷移させるか
	int changeTimeCount;							//ステージ遷移カウント
	int maxTime;									//マックスステージ遷移カウント
	float pushCount;								//ステージ切り替えカウント

	int frame;
	//静的定数
	static const float PUSH_INTERVAL;				//切り替えカウントのインターバル

};