#pragma once

#include "SceneBase.h"
#include "SceneManager.h"
#include <string>

class FadeManager;

using namespace std;

/// <summary>
/// ステージ選択画面クラス
/// </summary>
class StageSelection final : public SceneBase
{
public:
	 StageSelection(SceneManager* const sceneManager);
	~StageSelection();

	void Initialize();								//初期化処理
	void Finalize();								//終了処理
	void Activate();								//活性化処理
	void Update(float deltaTime);					//更新処理
	void Draw();									//描画処理


private:
	StageSelection(const StageSelection&);			//コピーコンストラクタ

	int StageCreator(int stageNumber);
	int stageDecrement(int stageNumber);			//選択ステージを1個前に持っていく
	int stageIncrement(int stageNumber);			//選択ステージを1個先に持っていく


	FadeManager* fadeManager;

	int font;										//ゲームフォント
	int arrowKeyImage;								//矢印キー画像
	int enterKeyImage;								//エンターキー画像
	int stageMapHandle[2];							//ステージマップの画像ハンドル
	int stageDescription[2];						//ステージの説明画像ハンドル
	int stageMax;									//最大ステージ数
	int stageNo;									//ステージナンバー
	bool changeScene;								//シーンを遷移させるか
	int changeTimeCount;							//ステージ遷移カウント
	int maxTime;									//マックスステージ遷移カウント


	//静的定数
	static const string IMAGE_FOLDER_PATH;			//imageフォルダまでのパス
	static const string ARROW_KEY_PATH;				//矢印キー画像のパス
	static const string ENTER_KEY_PATH;				//エンターキー画像のパス
	static const string STAGE1_MAP_PATH;			//ステージ1マップの画像のパス
	static const string STAGE2_MAP_PATH;			//ステージ2マップの画像のパス
	static const string STAGE1_DESCRIPTION_PAHT;	//ステージ1の説明画像のパス
	static const string STAGE2_DESCRIPTION_PAHT;	//ステージ2の説明画像のパス
	static const int	STAGE_IMAGE_NUMBER;			//ステージ画像数
};