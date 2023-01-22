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

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();


private:
	StageSelection(const StageSelection&);		//コピーコンストラクタ

	int StageCreator(int stageNum);
	int stageDecrement(int stageNum);     //選択ステージを1個前に
	int stageIncrement(int stageNum);     //選択ステージを1個先に


	FadeManager* fadeManager;

	int font;					//ゲームフォント
	int selectionHandle;		//ステージ選択画像ハンドル
	int stage1MapHandle;		//ステージ1マップの画像ハンドル
	int stage1Description;		//ステージ1の説明画像ハンドル
	int stage2MapHandle;		//ステージ2マップの画像ハンドル
	int stage2Description;		//ステージ2の説明画像ハンドル
	int stageMax;				//最大ステージ数
	int stageNo;				//ステージナンバー
	bool changeScene;			//シーンを遷移させるか
	int changeTimeCount;		//ステージ遷移カウント
	int maxTime;				//マックスステージ遷移カウント


	//静的定数
	static const string IMAGE_FOLDER_PATH;			//imageフォルダまでのパス
	static const string SELECTION_PATH;				//選択画像のパス
	static const string STAGE1_MAP_PATH;			//ステージ1マップの画像のパス
	static const string STAGE1_DESCRIPTION_PAHT;	//ステージ1の説明画像のパス
	static const string STAGE2_MAP_PATH;			//ステージ2マップの画像のパス
	static const string STAGE2_DESCRIPTION_PAHT;	//ステージ2の説明画像のパス

};