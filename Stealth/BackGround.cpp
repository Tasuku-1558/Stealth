#include "BackGround.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
BackGround::BackGround()
	: backGroundHandle(0)
	, PLAY_POSITION(0)
	, VIDEO_FOLDER_PATH("Data/Video/")
	, BACKGROUND_VIDEO_PATH("BackGround.mp4")
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
BackGround::~BackGround()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void BackGround::Initialize()
{
	//背景動画の読み込み
	backGroundHandle = LoadGraph(Input::InputPath(VIDEO_FOLDER_PATH, BACKGROUND_VIDEO_PATH).c_str());
}

/// <summary>
/// 終了処理
/// </summary>
void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
}

/// <summary>
/// 更新処理
/// </summary>
void BackGround::Update()
{
	//背景動画を再生中
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		//動画が終了したら0秒の所からまた再生する
		SeekMovieToGraph(backGroundHandle, PLAY_POSITION);

		//動画を再生する
		PlayMovieToGraph(backGroundHandle);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void BackGround::Draw()
{
	//背景動画を再生する
	DrawGraph(0, 0, backGroundHandle, FALSE);
}