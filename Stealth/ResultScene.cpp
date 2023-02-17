#include "ResultScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Camera.h"
#include "FireWorksParticle.h"
#include "FadeManager.h"
#include "Set.h"


char GameClear[] = { "GAME CLEAR" };
char GameOver[]  = { "GAME OVER" };

const string ResultScene::IMAGE_FOLDER_PATH		 = "data/image/";			//image�t�H���_�܂ł̃p�X
const string ResultScene::RESULT_UI_PATH		 = "resultUi.png";			//���U���g��ʂ�UI�̃p�X
const string ResultScene::RESULT_BACKGROUND_PATH = "resultBackGround.png";	//���U���g��ʂ̔w�i�摜�̃p�X
const int    ResultScene::PARTICLE_NUMBER		 = 500;						//�p�[�e�B�N���̐�


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, frame(0.0f)
	, fireWorksParticle()
	, camera(nullptr)
	, particleFlag(false)
	, particleInterval(0.0f)
	, fadeManager(nullptr)
	, clear(false)
	, resultUiImage(0)
	, alpha(0)
	, inc(0)
	, prevAlpha(0)
	, title(false)
	, selection(false)
	, backGroundImage(0)
	, backGroundX(0)
	, backGroundY(0)
{
	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Initialize()
{
	camera = new Camera();
	camera->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();

	resultUiImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	backGroundImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_BACKGROUND_PATH).c_str());

	alpha = 255;
	inc = -3;
}

string ResultScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// �I������
/// </summary>
void ResultScene::Finalize()
{
	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);

	DeleteGraph(backGroundImage);

	SafeDelete(fadeManager);

	SafeDelete(camera);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		SafeDelete(fireWorksParticlePtr);
		DeleteFireWorksParticle(fireWorksParticlePtr);
	}

	DeleteGraph(resultUiImage);
}

/// <summary>
/// �ԉ΃p�[�e�B�N����o�^
/// </summary>
/// <param name="newFireWorksParticle"></param>
void ResultScene::EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle)
{
	fireWorksParticle.emplace_back(newFireWorksParticle);
}

/// <summary>
/// �ԉ΃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteFireWorksParticle"></param>
void ResultScene::DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle)
{
	//�ԉ΂̃p�[�e�B�N���I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(fireWorksParticle.begin(), fireWorksParticle.end(), deleteFireWorksParticle);

	if (iter != fireWorksParticle.end())
	{
		//�ԉ΂̃p�[�e�B�N���I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, fireWorksParticle.end() - 1);
		fireWorksParticle.pop_back();

		return;
	}
}

/// <summary>
/// �ԉ΃p�[�e�B�N���̏o��
/// </summary>
void ResultScene::FireWorksParticlePop()
{
	if (!particleFlag)
	{
		//�p�[�e�B�N���̌����G���g���[����
		for (int i = 0; i < PARTICLE_NUMBER; i++)
		{
			//�p�[�e�B�N���̈ʒu�ƐF����͂���
			FireWorksParticle* newFireWorksParticle = new FireWorksParticle({ -500.0f,0.0f,0.0f }, GetColor(255, 255, 0));
			EntryFireWorksParticle(newFireWorksParticle);

			FireWorksParticle* newFireWorksParticle2 = new FireWorksParticle({ 600.0f,0.0f,0.0f }, GetColor(0, 128, 0));
			EntryFireWorksParticle(newFireWorksParticle2);

			FireWorksParticle* newFireWorksParticle3 = new FireWorksParticle({ 50.0f,0.0f,200.0f }, GetColor(240, 100, 100));
			EntryFireWorksParticle(newFireWorksParticle3);

			FireWorksParticle* newFireWorksParticle4 = new FireWorksParticle({ 50.0f,0.0f,-200.0f }, GetColor(128, 0, 128));
			EntryFireWorksParticle(newFireWorksParticle4);
		}

		particleFlag = true;
	}
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Activate()
{
	frame = 0.0f;

	clear = Set::GetInstance().GetResult();

	title = false;
	selection = false;

	font = CreateFontToHandle("Oranienbaum", 150, 1);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		DeleteFireWorksParticle(fireWorksParticlePtr);
		fireWorksParticlePtr->Activate();
	}

	fadeManager->Activate();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::Update(float deltaTime)
{
	camera->SelectionCamera();

	FireWorksParticlePop();
	
	//�p�[�e�B�N�����o������
	if (particleFlag)
	{
		particleInterval += deltaTime;
	
		//2�b�o�߂�����
		//�p�[�e�B�N�����ēx�o����悤�ɂ���
		if (particleInterval > 2.2f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}
	
	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Update(deltaTime);
	}

	BackGroundMove();
	
	SceneChange();

	ReturnScreen(deltaTime);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		//�p�[�e�B�N�����o���I�������
		if (fireWorksParticlePtr->IsParticleEnd())
		{
			DeleteFireWorksParticle(fireWorksParticlePtr);
		}
	}
}

/// <summary>
/// �V�[���؂�ւ�
/// </summary>
void ResultScene::SceneChange()
{
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		title = true;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		selection = true;
	}
}

/// <summary>
/// ��ʂ�J�ڂ���
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnScreen(float deltaTime)
{
	//�^�C�g����ʂȂ�
	if (title)
	{
		frame += deltaTime;

		fadeManager->FadeMove();

		//�t���[������2.2�b�o�߂�����
		if (frame > 2.2f)
		{
			//�^�C�g����ʂ֑J��
			parent->SetNextScene(SceneManager::TITLE);
			return;
		}
	}

	//�Z���N�V������ʂȂ�
	if (selection)
	{
		frame += deltaTime;

		fadeManager->FadeMove();

		//�t���[������2.2�b�o�߂�����
		if (frame > 2.2f)
		{
			//�X�e�[�W�I����ʂ֑J��
			parent->SetNextScene(SceneManager::SELECTION);
			return;
		}
	}
}

/// <summary>
/// �����̓_�ŏ���
/// </summary>
void ResultScene::Blink()
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

	DrawRotaGraph(1500, 1000, 0.5f, 0, resultUiImage, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// �w�i�摜�̓���
/// </summary>
void ResultScene::BackGroundMove()
{
	backGroundY += 2;

	//Y���W���[�ɂȂ�����
	if (backGroundY == 1080)
	{
		backGroundY = 0;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Draw()
{
	//�w�i�`��
	DrawGraph(backGroundX, backGroundY,  backGroundImage, TRUE);

	DrawGraph(backGroundX, backGroundY -1080, backGroundImage, TRUE);

	//�X�e�[�W�N���A�Ȃ��
	if (clear)
	{
		for (auto fireWorksParticlePtr : fireWorksParticle)
		{
			fireWorksParticlePtr->Draw();
		}

		DrawFormatStringToHandle(600, 400, GetColor(255, 215, 0), font, "%s", GameClear);
	}
	//�Q�[���I�[�o�[�Ȃ��
	else
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameOver);
	}

	Blink();

	fadeManager->Draw();
}