#include "TitleScene.h"
#include "DxLib.h"
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
	, titleMovie(0)
	, titleName(0)
	, titleUi(0)
	, alpha(0)
	, inc(0)
	, frame(0.0f)
	, sphereZ(0.0f)
	, VIDEO_FOLDER_PATH("Data/Video/")
	, IMAGE_FOLDER_PATH("Data/image/")
	, PLAY_VIDEO_PATH("PlayVideo.mp4")
	, TITLENAME_PATH("titleName.png")
	, TITLE_UI_PATH("titleUi.png")
	, START_SPHERE_POSY(-400.0f)
	, EXIT_SPHERE_POSY(-720.0f)
	, selectState(SelectState::START)
{
	Initialize();
	Activate();
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
	camera = new Camera();
	camera->SelectionAndResultCamera();

	light = new Light();

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

	delete camera;

	delete light;
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Activate()
{
	alpha = 255;
	inc = -3;

	//�^�C�g��BGM���Đ�
	SoundManager::GetInstance().PlayBgm(SoundManager::TITLE);
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
		SeekMovieToGraph(titleMovie, 0);

		//������Đ�����
		PlayMovieToGraph(titleMovie);
	}

	ChangeState();

	return nowSceneType;
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

			nowSceneType = SceneType::SELECTION;
		}

		//�����L�[�ŏ�Ԃ��I���ɂ���
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

			nowSceneType = SceneType::END;
		}

		//����L�[�ŏ�Ԃ��X�^�[�g�ɂ���
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP))
		{
			selectState = SelectState::START;
		}
	}
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

	if (selectState == SelectState::START)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 700, titleUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

		DrawGraph(400, 850, titleUi, TRUE);
	}

	if (selectState == SelectState::EXIT)
	{
		DrawGraph(400, 700, titleUi, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(400, 850, titleUi, TRUE);

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

	//�^�C�g���̏�Ԃɂ���ċ��̈ʒu��ς���
	if (selectState == SelectState::START)
	{
		sphereZ = START_SPHERE_POSY;
	}

	if (selectState == SelectState::EXIT)
	{
		sphereZ = EXIT_SPHERE_POSY;
	}

	//3D���̂̕`��
	DrawSphere3D({ -1250.0f, 0.0f, sphereZ }, 30.0f, 16, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
}