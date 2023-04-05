#include "TitleScene.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "FadeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
	: SceneBase(SceneType::TITLE)
	, titleState(TitleState::START)
	, titleMovie(0)
	, titleName(0)
	, startUi(0)
	, exitUi(0)
	, alpha(255)
	, inc(-3)
	, sceneChangeGame(false)
	, sceneChangeEnd(false)
	, spherePosition({ -520.0f, 1200.0f, 0.0f })
	, MAX_ALPHA(255)
	, PLAY_POSITION(0)
	, START_SPHERE_POS_Z(-220.0f)
	, EXIT_SPHERE_POS_Z(-350.0f)
	, SPHERE_RADIUS(20.0f)
	, VIDEO_FOLDER_PATH("Data/Video/")
	, IMAGE_FOLDER_PATH("Data/Image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, START_UI_PATH("startUi.png")
	, EXIT_UI_PATH("exitUi.png")
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(startUi);
}

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	light = new Light();

	camera = new Camera();
	camera->SelectionAndResultCamera();

	fadeManager = new FadeManager();

	//動画データの読み込み
	titleMovie = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

	//タイトルUIの読み込み
	titleName = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLENAME_PATH).c_str());

	startUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, START_UI_PATH).c_str());

	exitUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, EXIT_UI_PATH).c_str());

	//タイトルBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

/// <summary>
/// パスを入力
/// </summary>
/// <param name="folderPath">フォルダまでのパス</param>
/// <param name="path"></param>
/// <returns></returns>
string TitleScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
SceneType TitleScene::Update(float deltaTime)
{
	//デモ動画を再生中
	if (!GetMovieStateToGraph(titleMovie))
	{
		//動画が終了したら0秒の所からまた再生する
		SeekMovieToGraph(titleMovie, PLAY_POSITION);

		//動画を再生する
		PlayMovieToGraph(titleMovie);
	}

	//シーンが切り替わっていないならば
	if (!sceneChangeGame && !sceneChangeEnd)
	{
		ChangeState();
	}

	ReturnScreen();

	return nowSceneType;
}

/// <summary>
/// タイトルの状態の変更
/// </summary>
void TitleScene::ChangeState()
{
	//スタート状態なら
	if (titleState == TitleState::START)
	{
		spherePosition.z = START_SPHERE_POS_Z;

		//ステージ選択画面へ
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
		{
			sceneChangeGame = true;
		}

		//下矢印キーで状態を終了にする
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_DOWN))
		{
			titleState = TitleState::EXIT;
		}
	}

	//終了状態なら
	else
	{
		spherePosition.z = EXIT_SPHERE_POS_Z;

		//ゲームを終了する
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
		{
			sceneChangeEnd = true;
		}

		//上矢印キーで状態をスタートにする
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP))
		{
			titleState = TitleState::START;
		}
	}
}

/// <summary>
/// 画面を遷移する
/// </summary>
void TitleScene::ReturnScreen()
{
	if (sceneChangeGame)
	{
		//ステージ選択画面へ
		InputScene(SceneType::SELECTION);
	}

	if (sceneChangeEnd)
	{
		//ゲームを終了する
		InputScene(SceneType::END);
	}
}

/// <summary>
/// シーンを入力
/// </summary>
/// <param name="sceneType"></param>
void TitleScene::InputScene(SceneType sceneType)
{
	fadeManager->FadeMove();

	//フェードが終わったら
	if (fadeManager->FadeEnd())
	{
		//タイトルBGMを停止
		SoundManager::GetInstance().StopBgm();

		nowSceneType = sceneType;
	}
}

/// <summary>
/// 文字の点滅処理
/// </summary>
void TitleScene::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0 ||
		alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;

	//状態によって文字を点滅させる
	if (titleState == TitleState::START)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 700, startUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

		DrawGraph(400, 850, exitUi, TRUE);
	}
	else
	{
		DrawGraph(400, 700, startUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 850, exitUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Draw()
{
	//デモ動画を再生する
	DrawGraph(0, 0, titleMovie, FALSE);

	//タイトル名描画
	DrawRotaGraph(950, 450, 0.5f, 0, titleName, TRUE);

	Blink();

	//3D球体の描画
	DrawSphere3D(spherePosition, SPHERE_RADIUS, COLOR_BIT, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	fadeManager->Draw();
}