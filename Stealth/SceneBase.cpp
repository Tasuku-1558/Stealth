#include "SceneBase.h"
#include "TitleScene.h"
#include "StageSelection.h"
#include "GameScene.h"
#include "ResultScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneType"></param>
SceneBase::SceneBase(SceneType sceneType)
	: nowSceneType(sceneType)
	, number(0)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
	//処理なし
}

/// <summary>
/// 新しいシーンを生成する
/// </summary>
/// <param name="nowScene">現在のシーン</param>
/// <returns>次のシーン</returns>
SceneBase* SceneBase::CreateScene(SceneType nowScene)
{
	SceneBase* retScene = nullptr;
	StageSelection* stageSelection = nullptr;
	GameScene* gameScene = nullptr;

	switch (nowScene)
	{
	case SceneType::TITLE:
		retScene = new TitleScene();
		break;

	case SceneType::SELECTION:
		stageSelection = new StageSelection();
		number = stageSelection->GetStage();
		retScene = stageSelection;
		break;

	case SceneType::GAME:
		gameScene = new GameScene();
		gameScene->stage(number);
		retScene = gameScene;
		break;

	case SceneType::RESULT:
		retScene = new ResultScene();
		break;
	}

	return retScene;
}