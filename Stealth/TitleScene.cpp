#include "TitleScene.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "SceneManager.h"
#include "Camera.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "FadeManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, titleMovie(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
	, sphereZ(0.0f)
	, camera(nullptr)
	, fadeManager(nullptr)
	, VIDEO_FOLDER_PATH("data/video/")
	, IMAGE_FOLDER_PATH("data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
{
	//処理なし
	selectState = SelectState::START;
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	camera = new Camera;
	camera->Initialize();

	//動画データの読み込み
	titleMovie = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

	//画像UIの読み込み
	titleName = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLENAME_PATH).c_str());

	titleUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLE_UI_PATH).c_str());
}

/// <summary>
/// 画像のパスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string TitleScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
	PauseMovieToGraph(titleMovie);

	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);

	SafeDelete(camera);
}

/// <summary>
/// 活性化処理
/// </summary>
void TitleScene::Activate()
{
	selectState = SelectState::START;

	alpha = 255;
	inc = -3;

	//タイトルBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

/// <summary>
/// タイトルの状態の変更
/// </summary>
void TitleScene::ChangeState()
{
	//スタート状態なら
	if (selectState == SelectState::START)
	{
		//ステージ選択画面へ
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
		{
			//タイトルBGMを停止
			SoundManager::GetInstance().StopBgm();

			parent->SetNextScene(SceneManager::SELECTION);
			return;
		}
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_DOWN))
		{
			selectState = SelectState::EXIT;
		}

	}

	//終了状態なら
	else if (selectState == SelectState::EXIT)
	{
		//ゲームを終了する
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
		{
			//タイトルBGMを停止
			SoundManager::GetInstance().StopBgm();

			parent->SetNextScene(SceneManager::END);
			return;
		}
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP))
		{
			selectState = SelectState::START;
		}
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void TitleScene::Update(float deltaTime)
{
	camera->SelectionAndResultCamera();

	//デモ動画を再生
	if (!GetMovieStateToGraph(titleMovie))
	{
		SeekMovieToGraph(titleMovie, 0);

		PlayMovieToGraph(titleMovie);
	}

	ChangeState();
}

/// <summary>
/// 文字の点滅処理
/// </summary>
void TitleScene::Blink()
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

	DrawGraph(400, 700, titleUi, TRUE);

	DrawGraph(400, 850, titleUi, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Draw()
{
	DrawGraph(0, 0, titleMovie, FALSE);

	DrawRotaGraph(950, 450, 0.5f, 0, titleName, TRUE);

	//Blink();

	if (selectState == SelectState::START)
	{
		sphereZ = -400.0f;
	}

	if (selectState == SelectState::EXIT)
	{
		sphereZ = -720.0f;
	}

	DrawSphere3D(VGet(-1250.0f, 0.0f, sphereZ), 30.0f, 16, GetColor(255, 255, 0), GetColor(0, 0, 0), TRUE);
}