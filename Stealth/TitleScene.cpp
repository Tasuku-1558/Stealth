#include "TitleScene.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "SceneManager.h"
#include "Camera.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "FadeManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
TitleScene::TitleScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, titleMovie(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
	, sphereZ(0.0f)
	, camera(nullptr)
	, fadeManager(nullptr)
	, VIDEO_FOLDER_PATH("data/video/")
	, IMAGE_FOLDER_PATH("data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
{
	//�����Ȃ�
	selectState = SelectState::START;
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
	camera = new Camera;
	camera->Initialize();

	//����f�[�^�̓ǂݍ���
	titleMovie = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

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
	PauseMovieToGraph(titleMovie);

	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(titleUi);

	SafeDelete(camera);
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Activate()
{
	selectState = SelectState::START;

	alpha = 255;
	inc = -3;

	//�^�C�g��BGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

/// <summary>
/// �^�C�g���̏�Ԃ̕ύX
/// </summary>
void TitleScene::ChangeState()
{
	//�X�^�[�g��ԂȂ�
	if (selectState == SelectState::START)
	{
		//�X�e�[�W�I����ʂ�
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
		{
			//�^�C�g��BGM���~
			SoundManager::GetInstance().StopBgm();

			parent->SetNextScene(SceneManager::SELECTION);
			return;
		}
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_DOWN))
		{
			selectState = SelectState::EXIT;
		}

	}

	//�I����ԂȂ�
	else if (selectState == SelectState::EXIT)
	{
		//�Q�[�����I������
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
		{
			//�^�C�g��BGM���~
			SoundManager::GetInstance().StopBgm();

			parent->SetNextScene(SceneManager::END);
			return;
		}
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP))
		{
			selectState = SelectState::START;
		}
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void TitleScene::Update(float deltaTime)
{
	camera->SelectionAndResultCamera();

	//�f��������Đ�
	if (!GetMovieStateToGraph(titleMovie))
	{
		SeekMovieToGraph(titleMovie, 0);

		PlayMovieToGraph(titleMovie);
	}

	ChangeState();
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

	DrawGraph(400, 850, titleUi, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Draw()
{
	DrawGraph(0, 0, titleMovie, FALSE);

	DrawRotaGraph(950, 450, 0.5f, 0, titleName, TRUE);

	//Blink();

	if (selectState == SelectState::START)
	{
		sphereZ = -400.0f;
	}

	if (selectState == SelectState::EXIT)
	{
		sphereZ = -720.0f;
	}

	DrawSphere3D(VGet(-1250.0f, 0.0f, sphereZ), 30.0f, 16, GetColor(255, 255, 0), GetColor(0, 0, 0), TRUE);
}