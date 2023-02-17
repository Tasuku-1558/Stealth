#include "ResultScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Camera.h"
#include "FireWorksParticle.h"
#include "FadeManager.h"
#include "Set.h"


char GameClear[] = { "GAME CLEAR" };
char GameOver[]  = { "GAME OVER" };

const string ResultScene::IMAGE_FOLDER_PATH		 = "data/image/";			//imageフォルダまでのパス
const string ResultScene::RESULT_UI_PATH		 = "resultUi.png";			//リザルト画面のUIのパス
const string ResultScene::RESULT_BACKGROUND_PATH = "resultBackGround.png";	//リザルト画面の背景画像のパス
const int    ResultScene::PARTICLE_NUMBER		 = 500;						//パーティクルの数


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, frame(0.0f)
	, fireWorksParticle()
	, camera(nullptr)
	, particleFlag(false)
	, particleInterval(0.0f)
	, fadeManager(nullptr)
	, clear(false)
	, resultUiImage(0)
	, alpha(0)
	, inc(0)
	, prevAlpha(0)
	, title(false)
	, selection(false)
	, backGroundImage(0)
	, backGroundX(0)
	, backGroundY(0)
{
	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void ResultScene::Initialize()
{
	camera = new Camera();
	camera->Initialize();

	//画面効果クラス
	fadeManager = new FadeManager();

	resultUiImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	backGroundImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_BACKGROUND_PATH).c_str());

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
	//作成したフォントデータの削除
	DeleteFontToHandle(font);

	DeleteGraph(backGroundImage);

	SafeDelete(fadeManager);

	SafeDelete(camera);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		SafeDelete(fireWorksParticlePtr);
		DeleteFireWorksParticle(fireWorksParticlePtr);
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
		for (int i = 0; i < PARTICLE_NUMBER; i++)
		{
			//パーティクルの位置と色を入力する
			FireWorksParticle* newFireWorksParticle = new FireWorksParticle({ -500.0f,0.0f,0.0f }, GetColor(255, 255, 0));
			EntryFireWorksParticle(newFireWorksParticle);

			FireWorksParticle* newFireWorksParticle2 = new FireWorksParticle({ 600.0f,0.0f,0.0f }, GetColor(0, 128, 0));
			EntryFireWorksParticle(newFireWorksParticle2);

			FireWorksParticle* newFireWorksParticle3 = new FireWorksParticle({ 50.0f,0.0f,200.0f }, GetColor(240, 100, 100));
			EntryFireWorksParticle(newFireWorksParticle3);

			FireWorksParticle* newFireWorksParticle4 = new FireWorksParticle({ 50.0f,0.0f,-200.0f }, GetColor(128, 0, 128));
			EntryFireWorksParticle(newFireWorksParticle4);
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

	clear = Set::GetInstance().GetResult();

	title = false;
	selection = false;

	font = CreateFontToHandle("Oranienbaum", 150, 1);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		DeleteFireWorksParticle(fireWorksParticlePtr);
		fireWorksParticlePtr->Activate();
	}

	fadeManager->Activate();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::Update(float deltaTime)
{
	camera->SelectionCamera();

	FireWorksParticlePop();
	
	//パーティクルを出したら
	if (particleFlag)
	{
		particleInterval += deltaTime;
	
		//2秒経過したら
		//パーティクルを再度出せるようにする
		if (particleInterval > 2.2f)
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
	
	SceneChange();

	ReturnScreen(deltaTime);

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
/// 画面を遷移する
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnScreen(float deltaTime)
{
	//タイトル画面なら
	if (title)
	{
		frame += deltaTime;

		fadeManager->FadeMove();

		//フレーム数が2.2秒経過したら
		if (frame > 2.2f)
		{
			//タイトル画面へ遷移
			parent->SetNextScene(SceneManager::TITLE);
			return;
		}
	}

	//セレクション画面なら
	if (selection)
	{
		frame += deltaTime;

		fadeManager->FadeMove();

		//フレーム数が2.2秒経過したら
		if (frame > 2.2f)
		{
			//ステージ選択画面へ遷移
			parent->SetNextScene(SceneManager::SELECTION);
			return;
		}
	}
}

/// <summary>
/// 文字の点滅処理
/// </summary>
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
/// 背景画像の動き
/// </summary>
void ResultScene::BackGroundMove()
{
	backGroundY += 2;

	//Y座標が端になったら
	if (backGroundY == 1080)
	{
		backGroundY = 0;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Draw()
{
	//背景描画
	DrawGraph(backGroundX, backGroundY,  backGroundImage, TRUE);

	DrawGraph(backGroundX, backGroundY -1080, backGroundImage, TRUE);

	//ステージクリアならば
	if (clear)
	{
		for (auto fireWorksParticlePtr : fireWorksParticle)
		{
			fireWorksParticlePtr->Draw();
		}

		DrawFormatStringToHandle(600, 400, GetColor(255, 215, 0), font, "%s", GameClear);
	}
	//ゲームオーバーならば
	else
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameOver);
	}

	Blink();

	fadeManager->Draw();
}