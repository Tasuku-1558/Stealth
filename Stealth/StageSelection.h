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

	enum class State
	{
		STAGE1,
		STAGE2,
		TITLE,
	};

private:
	StageSelection(const StageSelection&);		//コピーコンストラクタ

	int StageCreator(int stageNum);
	int stageDecrement(int stageNum);     // 選択ステージを1個前に
	int stageIncrement(int stageNum);     // 選択ステージを1個先に


	FadeManager* fadeManager;


	State state;
	int selectionHandle;						//選択画像ハンドル
	int stageNumMax;
	int stageNo;
	int i;
	int frame;

	
	//静的定数
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string SELECTION_PATH;		//選択画像のパス
};