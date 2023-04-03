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
/// <returns>シーンを返す</returns>
SceneBase* SceneBase::CreateScene(SceneType nowScene)
{
	SceneBase* retScene = nullptr;

	switch (nowScene)
	{
	case SceneType::TITLE:
		retScene = new TitleScene();
		break;

	case SceneType::SELECTION:
		retScene = new StageSelection();
		break;

	case SceneType::GAME:
		retScene = new GameScene();
		break;

	case SceneType::RESULT:
		retScene = new ResultScene();
		break;
	}

	return retScene;
}