#include "ResultScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "FireWorksParticle.h"
#include "BackGround.h"
#include "FadeManager.h"
#include "Set.h"


char GameClear[] = { "GAME CLEAR" };
char GameOver[]  = { "GAME OVER" };

const string ResultScene::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string ResultScene::RESULT_UI_PATH	= "resultUi.png";		//リザルト画面のUIのパス


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, frame(0.0f)
	, fireWorksParticle()
	, backGround(nullptr)
	, particleFlag(false)
	, particleInterval(0.0f)
	, fadeManager(nullptr)
	, stageNo(0)
	, clear(false)
	, resultUiImage(0)
	, alpha(0)
	, inc(0)
	, prevAlpha(0)
	, title(false)
	, selection(false)
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
	//背景クラス
	backGround = new BackGround();
	backGround->Initialize();

	//画面効果クラス
	fadeManager = new FadeManager();

	resultUiImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	alpha = 255;
	inc = -3;
}

string ResultScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// 終了処理
/// </summary>
void ResultScene::Finalize()
{
	SafeDelete(backGround);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		SafeDelete(fireWorksParticlePtr);
	}

	DeleteGraph(resultUiImage);
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
			FireWorksParticle* newFireWorksParticle = new FireWorksParticle({ 500.0f,600.0f,0.0f });
			EntryFireWorksParticle(newFireWorksParticle);

			FireWorksParticle* newFireWorksParticle2 = new FireWorksParticle({ 1500.0f,600.0f,0.0f });
			EntryFireWorksParticle(newFireWorksParticle2);

			FireWorksParticle* newFireWorksParticle3 = new FireWorksParticle({ 1000.0f,800.0f,0.0f });
			EntryFireWorksParticle(newFireWorksParticle3);
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
	stageNo = Set::GetInstance().GetStage();

	clear = Set::GetInstance().GetResult();

	title = false;
	selection = false;

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
		title = true;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		selection = true;
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::Update(float deltaTime)
{
	FireWorksParticlePop();
	
	//パーティクルを出したら
	if (particleFlag)
	{
		particleInterval += deltaTime;
	
		//5秒経過したら
		//パーティクルを再度出せるようにする
		if (particleInterval > 2.0f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}
	
	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Update(deltaTime);
	}
	
	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		//パーティクルを出し終わったら
		if (fireWorksParticlePtr->IsParticleEnd())
		{
			DeleteFireWorksParticle(fireWorksParticlePtr);
		}
	}
	
	SceneChange();

	ReturnTitle(deltaTime);
	ReturnSelection(deltaTime);
}

/// <summary>
/// タイトル画面へ
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnTitle(float deltaTime)
{
	if (title)
	{
		frame += deltaTime;

		fadeManager->FadeMove();

		//フレーム数が2.4秒経過したら
		if (frame > 2.4f)
		{
			//タイトル画面へ遷移
			parent->SetNextScene(SceneManager::TITLE);
		}
	}
}

/// <summary>
/// セレクション画面へ
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnSelection(float deltaTime)
{
	if (selection)
	{
		frame += deltaTime;

		fadeManager->FadeMove();

		//フレーム数が2.4秒経過したら
		if (frame > 2.4f)
		{
			//ステージ選択画面へ遷移
			parent->SetNextScene(SceneManager::SELECTION);
		}
	}
}

void ResultScene::Blink()
{
	if (alpha > 255 && inc > 0)
	{
		inc *= -1;
	}

	if (alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawRotaGraph(1500, 1000, 0.5f, 0, resultUiImage, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Draw()
{
	//背景描画
	//backGround->Draw();

	//ステージクリアならば
	if (clear)
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 215, 0), font, "%s", GameClear);

	}
	//ゲームオーバーならば
	else
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameOver);
	}

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Draw();
	}

	Blink();

	fadeManager->Draw();
}