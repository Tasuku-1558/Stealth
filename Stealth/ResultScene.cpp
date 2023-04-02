#include "ResultScene.h"
#include "PreCompiledHeader.h"
#include "Camera.h"
#include "FireWorksParticle.h"
#include "FadeManager.h"
#include "KeyManager.h"
#include "Set.h"


char gameClear[] = { "GAME CLEAR" };
char gameOver[] = { "GAME OVER" };


/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
	: SceneBase(SceneType::RESULT)
	, fontHandle(0)
	, resultUiImage(0)
	, alpha(255)
	, inc(-3)
	, prevAlpha(0)
	, backGroundImage(0)
	, backGroundX(0)
	, backGroundY(0)
	, frame(0.0f)
	, fireWorksParticle()
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(false)
	, titleFlag(false)
	, selectionFlag(false)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, RESULT_UI_PATH("resultUi.png")
	, RESULT_BACKGROUND_PATH("resultBackGround.png")
	, PARTICLE_NUMBER(500)
	, MAX_ALPHA(255)
	, BACKGROUND_Y_INCREASE(2)
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	DeleteFontToHandle(fontHandle);
}

/// <summary>
/// 初期化処理
/// </summary>
void ResultScene::Initialize()
{
	camera = new Camera();

	fadeManager = new FadeManager();

	//リザルトUI画像の読み込み
	resultUiImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	backGroundImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_BACKGROUND_PATH).c_str());

	clear = Set::GetInstance().GetResult();

	fontHandle = CreateFontToHandle("Oranienbaum", 150, 1);
}

/// <summary>
/// 画像のパスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string ResultScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
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
		for (int i = 0; i < PARTICLE_NUMBER; i++)
		{
			//パーティクルの位置と色を入力する
			FireWorksParticle* newFireWorksParticle = new FireWorksParticle({ -500.0f,0.0f,0.0f }, GetColor(255, 255, 0));
			EntryFireWorksParticle(newFireWorksParticle);

			FireWorksParticle* newFireWorksParticle2 = new FireWorksParticle({ 600.0f,0.0f,0.0f }, GetColor(0, 128, 0));
			EntryFireWorksParticle(newFireWorksParticle2);

			FireWorksParticle* newFireWorksParticle3 = new FireWorksParticle({ 50.0f,0.0f,200.0f }, GetColor(240, 100, 100));
			EntryFireWorksParticle(newFireWorksParticle3);

			/*FireWorksParticle* newFireWorksParticle4 = new FireWorksParticle({ 50.0f,0.0f,-200.0f }, GetColor(128, 0, 128));
			EntryFireWorksParticle(newFireWorksParticle4);*/

		}

		particleFlag = true;
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
SceneType ResultScene::Update(float deltaTime)
{
	camera->SelectionAndResultCamera();

	FireWorksParticlePop();
	
	//パーティクルを出したら
	if (particleFlag)
	{
		particleInterval += deltaTime;
	
		//2秒経過したら
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

	BackGroundMove();
	
	//どのシーンにも遷移していないならば
	if (!titleFlag && !selectionFlag)
	{
		SceneChange();
	}

	ReturnScreen();

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		//パーティクルを出し終わったら
		if (fireWorksParticlePtr->IsParticleEnd())
		{
			DeleteFireWorksParticle(fireWorksParticlePtr);
		}
	}

	return nowSceneType;
}

/// <summary>
/// シーン切り替え
/// </summary>
void ResultScene::SceneChange()
{
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_BACK))
	{
		titleFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		selectionFlag = true;
	}
}

/// <summary>
/// シーンを入力
/// </summary>
/// <param name="sceneType"></param>
void ResultScene::InputScene(SceneType sceneType)
{
	fadeManager->FadeMove();

	//フェードが終わったら
	if (fadeManager->FadeEnd())
	{
		nowSceneType = sceneType;
	}
}

/// <summary>
/// 画面を遷移する
/// </summary>
void ResultScene::ReturnScreen()
{
	if (titleFlag)
	{
		//タイトル画面へ遷移
		InputScene(SceneType::TITLE);
	}

	if (selectionFlag)
	{
		//ステージ選択画面へ遷移
		InputScene(SceneType::SELECTION);
	}
}

/// <summary>
/// 文字の点滅処理
/// </summary>
void ResultScene::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0 ||
		alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawRotaGraph(1500, 1000, 0.5f, 0, resultUiImage, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// 背景画像の動き
/// </summary>
void ResultScene::BackGroundMove()
{
	backGroundY += BACKGROUND_Y_INCREASE;

	//Y座標がスクリーン端になったら
	if (backGroundY == SCREEN_HEIGHT)
	{
		backGroundY = 0;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Draw()
{
	DrawGraph(backGroundX, backGroundY,  backGroundImage, TRUE);

	DrawGraph(backGroundX, backGroundY - SCREEN_HEIGHT, backGroundImage, TRUE);

	//ゲームクリアならば
	if (clear)
	{
		for (auto fireWorksParticlePtr : fireWorksParticle)
		{
			fireWorksParticlePtr->Draw();
		}

		DrawFormatStringToHandle(600, 400, GetColor(255, 215, 0), fontHandle, "%s", gameClear);
	}
	//ゲームオーバーならば
	else
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), fontHandle, "%s", gameOver);
	}

	Blink();

	fadeManager->Draw();
}