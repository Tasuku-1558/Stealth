#include "BackGround.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
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
	//�w�i����̓ǂݍ���
	backGroundHandle = LoadGraph(Input::InputPath(VIDEO_FOLDER_PATH, BACKGROUND_VIDEO_PATH).c_str());
}

/// <summary>
/// �I������
/// </summary>
void BackGround::Finalize()
{
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
		SeekMovieToGraph(backGroundHandle, PLAY_POSITION);

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