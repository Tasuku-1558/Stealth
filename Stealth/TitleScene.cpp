#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"

const string TitleScene::VIDEO_FOLDER_PATH = "data/video/";		//videoフォルダまでのパス
const string TitleScene::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string TitleScene::PLAY_VIDEO_PATH   = "PlayVideo.mp4";	//タイトル動画のパス
const string TitleScene::TITLENAME_PATH	   = "titleName.png";	//タイトル名の画像のパス
const string TitleScene::TITLE_UI_PATH	   = "titleUi.png";		//プレイシーンへ遷移キーのUIのパス


TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, backGroundHandle(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(3)
{
	//処理なし
}

TitleScene::~TitleScene()
{
	if (backGroundHandle != NULL)
	{
		Finalize();
	}
}

void TitleScene::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + PLAY_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + TITLENAME_PATH;
	titleName = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + TITLE_UI_PATH;
	titleUi = LoadGraph(failePath.c_str());
}

void TitleScene::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

void TitleScene::Activate()
{
}

void TitleScene::Update(float deltaTime)
{
	//次のシーンへ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}
}

/// <summary>
/// 文字の点滅
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

void TitleScene::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);

	if (GetMovieStateToGraph(backGroundHandle) == 0)
	{
		SeekMovieToGraph(backGroundHandle, 5000);

		PlayMovieToGraph(backGroundHandle);
	}

	DrawGraph(750, 450, titleName, TRUE);

	Blink();
}