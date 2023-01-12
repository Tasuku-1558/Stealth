#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "TitleScene.h"
#include "StageSelection.h"
#include "PlayScene.h"
#include "Stage2.h"

SceneManager::SceneManager()
	: eachScene()
	, nowPointer(nullptr)
	, nowScene()
	, nextScene()
{
	//処理なし
}

SceneManager::~SceneManager()
{
	//処理なし
}

void SceneManager::Initialize()
{
	eachScene[TITLE] = new TitleScene(this);
	eachScene[SELECTION] = new StageSelection(this);
	eachScene[STAGE1] = new PlayScene(this);
	eachScene[STAGE2] = new Stage2(this);

	
	//全てのシーンの初期化
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScene[i]->Initialize();
	}

	//最初のシーンの初期化と活性化
	nowScene = nextScene = TITLE;

	nowPointer = eachScene[nowScene];
	nowPointer->Activate();
}

void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScene[i]->Finalize();
		SafeDelete(eachScene[i]);
	}
}

void SceneManager::Update(float deltaTime)
{
	//次のシーンがセットされていたら次へ
	if (nowScene != nextScene)
	{
		ChangeScene();						//次のシーン
	}

	if (nowPointer != nullptr)
	{
		nowPointer->Update(deltaTime);		//今のシーンの更新処理
	}
}

void SceneManager::Draw()
{
	if (nowPointer != nullptr)
	{
		nowPointer->Draw();					//今のシーンの描画処理
	}
}

void SceneManager::SetNextScene(Scene next)
{
	nextScene = next;
}

void SceneManager::ChangeScene()
{
	if (nextScene == END)
	{
		return;
	}

	nowPointer = eachScene[nextScene];	//次のシーンへ
	nowScene = nextScene;
	nowPointer->Activate();				//次のシーンを活性化
}

/// <summary>
/// 今のシーンを取得
/// </summary>
/// <returns></returns>
SceneManager::Scene SceneManager::GetNowScene()
{
	return nowScene;
}

/// <summary>
/// 次のシーンを取得
/// </summary>
/// <returns></returns>
SceneManager::Scene SceneManager::GetNextScene()
{
	return nextScene;
}