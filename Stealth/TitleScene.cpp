#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"


const string TitleScene::VIDEO_FOLDER_PATH = "data/video/";		//video�t�H���_�܂ł̃p�X
const string TitleScene::IMAGE_FOLDER_PATH = "data/image/";		//image�t�H���_�܂ł̃p�X
const string TitleScene::PLAY_VIDEO_PATH   = "PlayVideo.mp4";	//�^�C�g������̃p�X
const string TitleScene::TITLENAME_PATH	   = "titleName.png";	//�^�C�g�����̉摜�̃p�X
const string TitleScene::TITLE_UI_PATH	   = "titleUi.png";		//�X�e�[�W�I���V�[���֑J�ڃL�[��UI�̃p�X

using namespace std;

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
	, prevAlpha(0)
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

	alpha = 255;
	inc = -3;
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
std::string TitleScene::InputPath(string folderPath, string path)
{
	return std::string(folderPath + path);
}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize()
{
	DeleteGraph(backGroundHandle);
}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Activate()
{
	//�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void TitleScene::Update(float deltaTime)
{
	//���̃V�[����
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		parent->SetNextScene(SceneManager::SELECTION);
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
	/*alpha += inc;

	if (alpha <= 0 || alpha >= 255)
	{
		inc = -inc;
		alpha = prevAlpha;
	}

	prevAlpha = alpha;*/

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

	if (GetMovieStateToGraph(backGroundHandle) == 0)
	{
		SeekMovieToGraph(backGroundHandle, 5000);

		PlayMovieToGraph(backGroundHandle);
	}

	DrawGraph(750, 450, titleName, TRUE);

	Blink();
}