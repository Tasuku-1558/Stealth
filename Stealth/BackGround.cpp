#include "BackGround.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BackGround::BackGround()
	: backGroundHandle(0)
	, VIDEO_FOLDER_PATH("data/video/")
	, BACK_GROUND_VIDEO_PATH("BackGround.mp4")
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BackGround::~BackGround()
{
	Finalize();
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
	PauseMovieToGraph(backGroundHandle);

	DeleteGraph(backGroundHandle);
}

/// <summary>
/// ����������
/// </summary>
void BackGround::Activate()
{
	//�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
void BackGround::Update()
{
	//�w�i������Đ�
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		SeekMovieToGraph(backGroundHandle, 0);

		PlayMovieToGraph(backGroundHandle);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void BackGround::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);
}