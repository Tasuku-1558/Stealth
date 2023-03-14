#include "BackGround.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BackGround::BackGround()
	: backGroundHandle(0)
	, VIDEO_FOLDER_PATH("Data/Video/")
	, BACK_GROUND_VIDEO_PATH("BackGround.mp4")
{
	Initialize();
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
/// �X�V����
/// </summary>
void BackGround::Update()
{
	//�w�i������Đ���
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		//���悪�I��������0�b�̏�����܂��Đ�����
		SeekMovieToGraph(backGroundHandle, 0);

		//������Đ�����
		PlayMovieToGraph(backGroundHandle);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void BackGround::Draw()
{
	//�w�i������Đ�����
	DrawGraph(0, 0, backGroundHandle, FALSE);
}