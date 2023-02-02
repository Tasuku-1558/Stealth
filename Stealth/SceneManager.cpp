#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "TitleScene.h"
#include "StageSelection.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
	: eachScene()
	, nowPointer(nullptr)
	, nowScene()
	, nextScene()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneManager::Initialize()
{
	//各シーンを登録
	eachScene[TITLE]	 = new TitleScene(this);
	eachScene[SELECTION] = new StageSelection(this);
	eachScene[STAGE1]	 = new FirstStage(this);
	eachScene[STAGE2]	 = new SecondStage(this);
	eachScene[STAGE3]	 = new ThirdStage(this);

	
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

/// <summary>
/// 終了処理
/// </summary>
void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScene[i]->Finalize();
		SafeDelete(eachScene[i]);
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void SceneManager::Update(float deltaTime)
{
	//次のシーンがセットされていたら次へ
	if (nowScene != nextScene)
	{
		ChangeScene();						//次のシーンへ
	}

	if (nowPointer != nullptr)
	{
		nowPointer->Update(deltaTime);		//今のシーンの更新処理
	}
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Draw()
{
	if (nowPointer != nullptr)
	{
		nowPointer->Draw();					//今のシーンの描画処理
	}
}

/// <summary>
/// 次のシーンをセット
/// </summary>
/// <param name="next"></param>
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