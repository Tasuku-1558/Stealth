#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "FadeManager.h"
#include "StageSelection.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, backGroundHandle(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
	, fadeManager(nullptr)
	, VIDEO_FOLDER_PATH("data/video/")
	, IMAGE_FOLDER_PATH("data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{
	//����f�[�^�̓ǂݍ���
	backGroundHandle = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

	//�摜UI�̓ǂݍ���
	titleName = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLENAME_PATH).c_str());

	titleUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLE_UI_PATH).c_str());
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string TitleScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize()
{
	PauseMovieToGraph(backGroundHandle);

	DeleteGraph(backGroundHandle);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Activate()
{
	alpha = 255;
	inc = -3;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void TitleScene::Update(float deltaTime)
{
	//�^�C�g��BGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);

	//�f��������Đ�
	if (!GetMovieStateToGraph(backGroundHandle))
	{
		SeekMovieToGraph(backGroundHandle, 0);

		PlayMovieToGraph(backGroundHandle);
	}

	//�X�e�[�W�I����ʂ�
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		//�^�C�g��BGM���~
		SoundManager::GetInstance().StopBgm();

		parent->SetNextScene(SceneManager::SELECTION);
		return;
		//retScene = new StageSelection();

	}

	//return retScene;
}

/// <summary>
/// �����̓_�ŏ���
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

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Draw()
{
	DrawGraph(0, 0, backGroundHandle, FALSE);

	DrawRotaGraph(950, 450, 0.5f, 0, titleName, TRUE);

	Blink();
}