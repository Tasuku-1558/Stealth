#include "TitleScene.h"
#include "DxLib.h"
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
	, titleMovie(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
	, sphereZ(0.0f)
	, VIDEO_FOLDER_PATH("Data/Video/")
	, IMAGE_FOLDER_PATH("Data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
	, START_SPHERE_POSY(-400.0f)
	, EXIT_SPHERE_POSY(-720.0f)
	, selectState(SelectState::START)
{
	Initialize();
	Activate();
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
	camera = new Camera();
	camera->SelectionAndResultCamera();

	light = new Light();

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

	delete camera;

	delete light;
}

/// <summary>
/// 活性化処理
/// </summary>
void TitleScene::Activate()
{
	alpha = 255;
	inc = -3;

	//タイトルBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
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
		SeekMovieToGraph(titleMovie, 0);

		//動画を再生する
		PlayMovieToGraph(titleMovie);
	}

	ChangeState();

	return nowSceneType;
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

			nowSceneType = SceneType::SELECTION;
		}

		//下矢印キーで状態を終了にする
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

			nowSceneType = SceneType::END;
		}

		//上矢印キーで状態をスタートにする
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP))
		{
			selectState = SelectState::START;
		}
	}
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

	if (selectState == SelectState::START)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 700, titleUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

		DrawGraph(400, 850, titleUi, TRUE);
	}

	if (selectState == SelectState::EXIT)
	{
		DrawGraph(400, 700, titleUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 850, titleUi, TRUE);

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

	//タイトルの状態によって球の位置を変える
	if (selectState == SelectState::START)
	{
		sphereZ = START_SPHERE_POSY;
	}

	if (selectState == SelectState::EXIT)
	{
		sphereZ = EXIT_SPHERE_POSY;
	}

	//3D球体の描画
	DrawSphere3D({ -1250.0f, 0.0f, sphereZ }, 30.0f, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
}