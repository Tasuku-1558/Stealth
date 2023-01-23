#include "BackGround.h"

const string BackGround::VIDEO_FOLDER_PATH		= "data/video/";		//videoフォルダまでのパス
const string BackGround::BACK_GROUND_VIDEO_PATH = "BackGround.mp4";		//背景動画のパス


/// <summary>
/// コンストラクタ
/// </summary>
BackGround::BackGround()
	: backGroundHandle(0)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
BackGround::~BackGround()
{
	if (backGroundHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void BackGround::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + BACK_GROUND_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());
}

/// <summary>
/// 終了処理
/// </summary>
void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

/// <summary>
/// 活性化処理
/// </summary>
void BackGround::Activate()
{
	//処理なし
}

/// <summary>
/// 描画処理
/// </summary>
void BackGround::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);

	if (GetMovieStateToGraph(backGroundHandle) == 0)
	{
		SeekMovieToGraph(backGroundHandle, 0);

		PlayMovieToGraph(backGroundHandle);
	}
}