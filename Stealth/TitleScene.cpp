#include "TitleScene.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "FadeManager.h"
#include "InputManager.h"

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
	, INC_SPEED(-1)
	, PLAY_POSITION(0)
	, START_UI_POS_X(400)
	, START_UI_POS_Y(700)
	, EXIT_UI_POS_X(400)
	, EXIT_UI_POS_Y(850)
	, TITLE_MOVIE_POS_X(0)
	, TITLE_MOVIE_POS_Y(0)
	, TITLE_NAME_POS_X(950)
	, TITLE_NAME_POS_Y(450)
	, SPHERE_DIFCOLOR(GetColor(255, 0, 0))
	, SPHERE_SPCCOLOR(GetColor(255, 255, 255))
	, START_SPHERE_POS_Z(-220.0f)
	, EXIT_SPHERE_POS_Z(-350.0f)
	, SPHERE_RADIUS(20.0f)
	, TITLE_NAME_SIZE(0.5)
	, TITLE_NAME_ANGLE(0.0)
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
	titleMovie = LoadGraph(Input::InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

	//タイトルUi画像の読み込み
	titleName = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, TITLENAME_PATH).c_str());

	startUi = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, START_UI_PATH).c_str());

	exitUi = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, EXIT_UI_PATH).c_str());

	//タイトルBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
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
/// <param name="sceneType">シーンの種類</param>
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
		inc *= INC_SPEED;
	}

	alpha += inc;

	//状態によって文字を点滅させる
	if (titleState == TitleState::START)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(START_UI_POS_X, START_UI_POS_Y, startUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);


		DrawGraph(EXIT_UI_POS_X, EXIT_UI_POS_Y, exitUi, TRUE);
	}
	else
	{
		DrawGraph(START_UI_POS_X, START_UI_POS_Y, startUi, TRUE);


		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(EXIT_UI_POS_X, EXIT_UI_POS_Y, exitUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Draw()
{
	//デモ動画を再生する
	DrawGraph(TITLE_MOVIE_POS_X, TITLE_MOVIE_POS_Y, titleMovie, FALSE);

	//タイトル名描画
	DrawRotaGraph(TITLE_NAME_POS_X, TITLE_NAME_POS_Y, TITLE_NAME_SIZE, TITLE_NAME_ANGLE, titleName, TRUE);

	Blink();

	//3D球体の描画
	DrawSphere3D(spherePosition, SPHERE_RADIUS, COLOR_BIT, SPHERE_DIFCOLOR, SPHERE_SPCCOLOR, TRUE);

	fadeManager->Draw();
}