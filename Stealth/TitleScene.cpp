#include "TitleScene.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "FadeManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
	: SceneBase(SceneType::TITLE)
	, titleState(TitleState::START)
	, titleMovie(0)
	, titleName(0)
	, startUi(0)
	, exitUi(0)
	, alpha(255)
	, inc(-3)
	, sceneChangeGame(false)
	, sceneChangeEnd(false)
	, spherePosition({ -520.0f, 1200.0f, 0.0f })
	, MAX_ALPHA(255)
	, PLAY_POSITION(0)
	, START_SPHERE_POS_Z(-220.0f)
	, EXIT_SPHERE_POS_Z(-350.0f)
	, SPHERE_RADIUS(20.0f)
	, VIDEO_FOLDER_PATH("Data/Video/")
	, IMAGE_FOLDER_PATH("Data/Image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, START_UI_PATH("startUi.png")
	, EXIT_UI_PATH("exitUi.png")
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	DeleteGraph(titleMovie);

	DeleteGraph(titleName);

	DeleteGraph(startUi);
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{
	light = new Light();

	camera = new Camera();
	camera->SelectionAndResultCamera();

	fadeManager = new FadeManager();

	//����f�[�^�̓ǂݍ���
	titleMovie = LoadGraph(InputPath(VIDEO_FOLDER_PATH, PLAY_VIDEO_PATH).c_str());

	//�^�C�g��UI�̓ǂݍ���
	titleName = LoadGraph(InputPath(IMAGE_FOLDER_PATH, TITLENAME_PATH).c_str());

	startUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, START_UI_PATH).c_str());

	exitUi = LoadGraph(InputPath(IMAGE_FOLDER_PATH, EXIT_UI_PATH).c_str());

	//�^�C�g��BGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
}

/// <summary>
/// �p�X�����
/// </summary>
/// <param name="folderPath">�t�H���_�܂ł̃p�X</param>
/// <param name="path"></param>
/// <returns></returns>
string TitleScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
SceneType TitleScene::Update(float deltaTime)
{
	//�f��������Đ���
	if (!GetMovieStateToGraph(titleMovie))
	{
		//���悪�I��������0�b�̏�����܂��Đ�����
		SeekMovieToGraph(titleMovie, PLAY_POSITION);

		//������Đ�����
		PlayMovieToGraph(titleMovie);
	}

	//�V�[�����؂�ւ���Ă��Ȃ��Ȃ��
	if (!sceneChangeGame && !sceneChangeEnd)
	{
		ChangeState();
	}

	ReturnScreen();

	return nowSceneType;
}

/// <summary>
/// �^�C�g���̏�Ԃ̕ύX
/// </summary>
void TitleScene::ChangeState()
{
	//�X�^�[�g��ԂȂ�
	if (titleState == TitleState::START)
	{
		spherePosition.z = START_SPHERE_POS_Z;

		//�X�e�[�W�I����ʂ�
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
		{
			sceneChangeGame = true;
		}

		//�����L�[�ŏ�Ԃ��I���ɂ���
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_DOWN))
		{
			titleState = TitleState::EXIT;
		}
	}

	//�I����ԂȂ�
	else
	{
		spherePosition.z = EXIT_SPHERE_POS_Z;

		//�Q�[�����I������
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
		{
			sceneChangeEnd = true;
		}

		//����L�[�ŏ�Ԃ��X�^�[�g�ɂ���
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP))
		{
			titleState = TitleState::START;
		}
	}
}

/// <summary>
/// ��ʂ�J�ڂ���
/// </summary>
void TitleScene::ReturnScreen()
{
	if (sceneChangeGame)
	{
		//�X�e�[�W�I����ʂ�
		InputScene(SceneType::SELECTION);
	}

	if (sceneChangeEnd)
	{
		//�Q�[�����I������
		InputScene(SceneType::END);
	}
}

/// <summary>
/// �V�[�������
/// </summary>
/// <param name="sceneType"></param>
void TitleScene::InputScene(SceneType sceneType)
{
	fadeManager->FadeMove();

	//�t�F�[�h���I�������
	if (fadeManager->FadeEnd())
	{
		//�^�C�g��BGM���~
		SoundManager::GetInstance().StopBgm();

		nowSceneType = sceneType;
	}
}

/// <summary>
/// �����̓_�ŏ���
/// </summary>
void TitleScene::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0 ||
		alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;

	//��Ԃɂ���ĕ�����_�ł�����
	if (titleState == TitleState::START)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 700, startUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

		DrawGraph(400, 850, exitUi, TRUE);
	}
	else
	{
		DrawGraph(400, 700, startUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 850, exitUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Draw()
{
	//�f��������Đ�����
	DrawGraph(0, 0, titleMovie, FALSE);

	//�^�C�g�����`��
	DrawRotaGraph(950, 450, 0.5f, 0, titleName, TRUE);

	Blink();

	//3D���̂̕`��
	DrawSphere3D(spherePosition, SPHERE_RADIUS, COLOR_BIT, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	fadeManager->Draw();
}