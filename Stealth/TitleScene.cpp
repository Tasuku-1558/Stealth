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
	, alpha(255)
	, inc(-3)
	, frame(0.0f)
	, spherePosition({ -520.0f, 1200.0f, 0.0f })
	, VIDEO_FOLDER_PATH("Data/Video/")
	, IMAGE_FOLDER_PATH("Data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
	, MAX_ALPHA(255)
	, START_SPHERE_POSY(-220.0f)
	, EXIT_SPHERE_POSY(-350.0f)
	, titleState(TitleState::START)
{
	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	//処理なし
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

	//UI画像の読み込み
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
/// 活性化処理
/// </summary>
void TitleScene::Activate()
{
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
	if (titleState == TitleState::START)
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
			titleState = TitleState::EXIT;
		}
	}

	//終了状態なら
	else
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
			titleState = TitleState::START;
		}
	}
}

/// <summary>
/// 文字の点滅処理
/// </summary>
void TitleScene::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0)
	{
		inc *= -1;
	}
		
	if (alpha < 0 && inc < 0)
	{
		inc *= -1;
	}
		
	alpha += inc;

	//状態によって文字を点滅させる
	if (titleState == TitleState::START)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 700, titleUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

		DrawGraph(400, 850, titleUi, TRUE);
	}
	else
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
	if (titleState == TitleState::START)
	{
		spherePosition.z = START_SPHERE_POSY;
	}
	else
	{
		spherePosition.z = EXIT_SPHERE_POSY;
	}

	//3D球体の描画
	DrawSphere3D(spherePosition, 20.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}