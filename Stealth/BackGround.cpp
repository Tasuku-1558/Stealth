#include "BackGround.h"

const string BackGround::VIDEO_FOLDER_PATH		= "data/video/";		//video�t�H���_�܂ł̃p�X
const string BackGround::BACK_GROUND_VIDEO_PATH = "BackGround.mp4";		//�w�i����̃p�X


/// <summary>
/// �R���X�g���N�^
/// </summary>
BackGround::BackGround()
	: backGroundHandle(0)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BackGround::~BackGround()
{
	if (backGroundHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void BackGround::Initialize()
{
	string failePath = VIDEO_FOLDER_PATH + BACK_GROUND_VIDEO_PATH;
	backGroundHandle = LoadGraph(failePath.c_str());
}

/// <summary>
/// �I������
/// </summary>
void BackGround::Finalize()
{
	DeleteGraph(backGroundHandle);
	backGroundHandle = NULL;
}

/// <summary>
/// ����������
/// </summary>
void BackGround::Activate()
{
	//�����Ȃ�
}

/// <summary>
/// �`�揈��
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