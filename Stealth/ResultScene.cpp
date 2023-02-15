#include "ResultScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "FireWorksParticle.h"
#include "FadeManager.h"
#include "Set.h"


char GameClear[] = { "GAME CLEAR" };
char GameOver[]  = { "GAME OVER" };


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, frame(0.0f)
	, fireWorksParticle()
	, pUpdate(nullptr)
	, particleFlag(false)
	, particleInterval(0.0f)
	, fadeManager(nullptr)
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
	//画面効果クラス
	fadeManager = new FadeManager();
}

/// <summary>
/// 終了処理
/// </summary>
void ResultScene::Finalize()
{
	//作成したフォントデータの削除
	DeleteFontToHandle(font);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		SafeDelete(fireWorksParticlePtr);
	}
}

/// <summary>
/// 花火パーティクルを登録
/// </summary>
/// <param name="newFireWorksParticle"></param>
void ResultScene::EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle)
{
	fireWorksParticle.emplace_back(newFireWorksParticle);
}

/// <summary>
/// 花火パーティクルを削除
/// </summary>
/// <param name="deleteFireWorksParticle"></param>
void ResultScene::DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle)
{
	//花火のパーティクルオブジェクトから検索して削除
	auto iter = std::find(fireWorksParticle.begin(), fireWorksParticle.end(), deleteFireWorksParticle);

	if (iter != fireWorksParticle.end())
	{
		//花火のパーティクルオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, fireWorksParticle.end() - 1);
		fireWorksParticle.pop_back();

		return;
	}
}

/// <summary>
/// 花火パーティクルの出現
/// </summary>
void ResultScene::FireWorksParticlePop()
{
	if (!particleFlag)
	{
		//パーティクルの個数分エントリーする
		for (int i = 0; i < 500; i++)
		{
			FireWorksParticle* newFireWorksParticle = new FireWorksParticle({ 5000.0f,0.0f,0.0f });
			EntryFireWorksParticle(newFireWorksParticle);
		}

		particleFlag = true;
	}
}

/// <summary>
/// 活性化処理
/// </summary>
void ResultScene::Activate()
{
	frame = 0.0f;
	pUpdate = &ResultScene::UpdateGame;

	font = CreateFontToHandle("Oranienbaum", 150, 1);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Activate();
	}

	fadeManager->Activate();
}

/// <summary>
/// シーン切り替え
/// </summary>
void ResultScene::SceneChange()
{
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		pUpdate = &ResultScene::ReturnTitle;
	}
	if (CheckHitKey(KEY_INPUT_G))
	{
		pUpdate = &ResultScene::ReturnSelection;
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::UpdateGame(float deltaTime)
{
	FireWorksParticlePop();

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Update(deltaTime);
	}

	//パーティクルを出したら
	if (particleFlag)
	{
		particleInterval += deltaTime;

		//5秒経過したら
		//パーティクルを再度出せるようにする
		if (particleInterval > 1.0f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}

	SceneChange();

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		//パーティクルを出し終わったら
		if (fireWorksParticlePtr->IsParticleEnd())
		{
			DeleteFireWorksParticle(fireWorksParticlePtr);
		}
	}
}

/// <summary>
/// タイトル画面へ
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnTitle(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//フレーム数が2.8秒経過したら
	if (frame > 2.8f)
	{
		//タイトル画面へ遷移
		parent->SetNextScene(SceneManager::TITLE);
	}
}

/// <summary>
/// セレクション画面へ
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnSelection(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//フレーム数が2.8秒経過したら
	if (frame > 2.8f)
	{
		//ステージ選択画面へ遷移
		parent->SetNextScene(SceneManager::SELECTION);
	}
}

/// <summary>
/// もう一度プレイ
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnStage(float deltaTime)
{
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Draw()
{
	//ステージクリアならば
	if (Set::GetInstance().GetResult())
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameClear);

		for (auto fireWorksParticlePtr : fireWorksParticle)
		{
			fireWorksParticlePtr->Draw();
		}

	}
	//ゲームオーバーならば
	else
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameOver);
	}

	fadeManager->Draw();

	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "ParticleSize : %d", fireWorksParticle.size());
}