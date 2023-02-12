#include "ResultScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "FireWorksParticle.h"

char GameClear[] = { "GAME CLEAR" };


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, fireWorksParticle(nullptr)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void ResultScene::Initialize()
{
	for (int i = 0; i < 50; i++)
	{
		fireWorksParticle = new FireWorksParticle({ 100.0f ,0.0f,-1000.0f });
		fireWorksParticle->Initialize();
	}
}

/// <summary>
/// 終了処理
/// </summary>
void ResultScene::Finalize()
{
	//作成したフォントデータの削除
	DeleteFontToHandle(font);

	SafeDelete(fireWorksParticle);
}

/// <summary>
/// 活性化処理
/// </summary>
void ResultScene::Activate()
{
	font = CreateFontToHandle("Oranienbaum", 150, 1);

	fireWorksParticle->Activate();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::Update(float deltaTime)
{
	fireWorksParticle->Update(deltaTime);
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Draw()
{
	DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameClear);

	fireWorksParticle->Draw();
}