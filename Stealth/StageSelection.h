#pragma once

#include "SceneBase.h"
#include "SceneManager.h"
#include <string>

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

	void StageCreator();

	int StageDecrement(int stageNum);     // 選択ステージを1個前に
	int StageIncrement(int stageNum);     // 選択ステージを1個先に

	int selectionHandle;						//選択画像ハンドル
	int stageNumMax;
	SceneManager::Scene scene;

	
	//静的定数
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string SELECTION_PATH;		//選択画像のパス
};