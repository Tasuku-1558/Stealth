#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"


const string TitleScene::VIDEO_FOLDER_PATH = "data/video/";		//videoフォルダまでのパス
const string TitleScene::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string TitleScene::PLAY_VIDEO_PATH   = "PlayVideo.mp4";	//タイトル動画のパス
const string TitleScene::TITLENAME_PATH	   = "titleName.png";	//タイトル名の画像のパス
const string TitleScene::TITLE_UI_PATH	   = "titleUi.png";		//ステージ選択シーンへ遷移キーのUIのパス


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
	, frame(0)
	, prevAlpha(0)
	, state()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	if (backGroundHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + PLAY_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + TITLENAME_PATH;
	titleName = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + TITLE_UI_PATH;
	titleUi = LoadGraph(failePath.c_str());

	alpha = 255;
	inc = -3;
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

/// <summary>
/// 活性化処理
/// </summary>
void TitleScene::Activate()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void TitleScene::Update(float deltaTime)
{
	//次のシーンへ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//inc *= 10;
		/*frame = 0;
		state = State::START;*/
		parent->SetNextScene(SceneManager::SELECTION);
	}

	/*if (state == State::START && frame >= 90)
	{
		
	}
	++frame;*/
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
	/*alpha += inc;

	if (alpha <= 0 || alpha >= 255)
	{
		inc = -inc;
		alpha = prevAlpha;
	}

	prevAlpha = alpha;*/

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

	if (GetMovieStateToGraph(backGroundHandle) == 0)
	{
		SeekMovieToGraph(backGroundHandle, 5000);

		PlayMovieToGraph(backGroundHandle);
	}

	DrawGraph(750, 450, titleName, TRUE);

	Blink();
}