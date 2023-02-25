#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "FadeManager.h"
#include "StageSelection.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, backGroundHandle(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
	, fadeManager(nullptr)
	, VIDEO_FOLDER_PATH("data/video/")
	, IMAGE_FOLDER_PATH("data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
{
	//処理なし
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
	//動画データの読み込み
	backGroundHandle = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

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
	PauseMovieToGraph(backGroundHandle);

	DeleteGraph(backGroundHandle);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);
}

/// <summary>
/// 活性化処理
/// </summary>
void TitleScene::Activate()
{
	alpha = 255;
	inc = -3;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void TitleScene::Update(float deltaTime)
{
	//タイトルBGMを再生
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);

	//デモ動画を再生
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		SeekMovieToGraph(backGroundHandle, 0);

		PlayMovieToGraph(backGroundHandle);
	}

	//ステージ選択画面へ
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		//タイトルBGMを停止
		SoundManager::GetInstance().StopBgm();

		parent->SetNextScene(SceneManager::SELECTION);
		return;
		//retScene = new StageSelection();

	}

	//return retScene;
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

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);

	DrawRotaGraph(950, 450, 0.5f, 0, titleName, TRUE);

	Blink();
}