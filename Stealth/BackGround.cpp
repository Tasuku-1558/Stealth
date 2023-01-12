#include "BackGround.h"

const string BackGround::VIDEO_FOLDER_PATH		= "data/video/";		//videoフォルダまでのパス
const string BackGround::BACK_GROUND_VIDEO_PATH = "BackGround.mp4";		//背景動画のパス


BackGround::BackGround()
	: backGroundHandle(0)
{
	//処理なし
}

BackGround::~BackGround()
{
	if (backGroundHandle != NULL)
	{
		Finalize();
	}
}

void BackGround::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + BACK_GROUND_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());
}

void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

void BackGround::Activate()
{
}

void BackGround::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);

	if (GetMovieStateToGraph(backGroundHandle) == 0)
	{
		SeekMovieToGraph(backGroundHandle, 0);

		PlayMovieToGraph(backGroundHandle);
	}
}