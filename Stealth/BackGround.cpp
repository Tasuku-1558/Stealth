#include "BackGround.h"


/// <summary>
/// コンストラクタ
/// </summary>
BackGround::BackGround()
	: backGroundHandle(0)
	, VIDEO_FOLDER_PATH("data/video/")
	, BACK_GROUND_VIDEO_PATH("BackGround.mp4")
{
	//処理なし
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
	string failePath = VIDEO_FOLDER_PATH + BACK_GROUND_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());
}

/// <summary>
/// 終了処理
/// </summary>
void BackGround::Finalize()
{
	PauseMovieToGraph(backGroundHandle);

	DeleteGraph(backGroundHandle);
}

/// <summary>
/// 活性化処理
/// </summary>
void BackGround::Activate()
{
	//処理なし
}

/// <summary>
/// 更新処理
/// </summary>
void BackGround::Update()
{
	//背景動画を再生
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		SeekMovieToGraph(backGroundHandle, 0);

		PlayMovieToGraph(backGroundHandle);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void BackGround::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);
}