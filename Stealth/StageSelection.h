#pragma once

#include "SceneBase.h"
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

	int selectionHandle;						//選択画像ハンドル

	//静的定数
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string SELECTION_PATH;		//選択画像のパス
};