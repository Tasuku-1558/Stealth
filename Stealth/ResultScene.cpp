#include "ResultScene.h"
#include "PreCompiledHeader.h"
#include "Camera.h"
#include "FireWorksParticle.h"
#include "FadeManager.h"
#include "KeyManager.h"
#include "Set.h"


char gameClear[] = { "GAME CLEAR" };
char gameOver[] = { "GAME OVER" };


/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultScene::ResultScene()
	: SceneBase(SceneType::RESULT)
	, fontHandle(0)
	, resultUiImage(0)
	, alpha(255)
	, inc(-3)
	, prevAlpha(0)
	, backGroundImage(0)
	, backGroundX(0)
	, backGroundY(0)
	, frame(0.0f)
	, fireWorksParticle()
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(false)
	, titleFlag(false)
	, selectionFlag(false)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, RESULT_UI_PATH("resultUi.png")
	, RESULT_BACKGROUND_PATH("resultBackGround.png")
	, PARTICLE_NUMBER(500)
	, MAX_ALPHA(255)
	, BACKGROUND_Y_INCREASE(2)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
	DeleteFontToHandle(fontHandle);
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Initialize()
{
	camera = new Camera();

	fadeManager = new FadeManager();

	//���U���gUI�摜�̓ǂݍ���
	resultUiImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	backGroundImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_BACKGROUND_PATH).c_str());

	clear = Set::GetInstance().GetResult();

	fontHandle = CreateFontToHandle("Oranienbaum", 150, 1);
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
string ResultScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
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

			/*FireWorksParticle* newFireWorksParticle4 = new FireWorksParticle({ 50.0f,0.0f,-200.0f }, GetColor(128, 0, 128));
			EntryFireWorksParticle(newFireWorksParticle4);*/

		}

		particleFlag = true;
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
SceneType ResultScene::Update(float deltaTime)
{
	camera->SelectionAndResultCamera();

	FireWorksParticlePop();
	
	//�p�[�e�B�N�����o������
	if (particleFlag)
	{
		particleInterval += deltaTime;
	
		//2�b�o�߂�����
		//�p�[�e�B�N�����ēx�o����悤�ɂ���
		if (particleInterval > 2.0f)
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
	
	//�ǂ̃V�[���ɂ��J�ڂ��Ă��Ȃ��Ȃ��
	if (!titleFlag && !selectionFlag)
	{
		SceneChange();
	}

	ReturnScreen();

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		//�p�[�e�B�N�����o���I�������
		if (fireWorksParticlePtr->IsParticleEnd())
		{
			DeleteFireWorksParticle(fireWorksParticlePtr);
		}
	}

	return nowSceneType;
}

/// <summary>
/// �V�[���؂�ւ�
/// </summary>
void ResultScene::SceneChange()
{
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_BACK))
	{
		titleFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		selectionFlag = true;
	}
}

/// <summary>
/// �V�[�������
/// </summary>
/// <param name="sceneType"></param>
void ResultScene::InputScene(SceneType sceneType)
{
	fadeManager->FadeMove();

	//�t�F�[�h���I�������
	if (fadeManager->FadeEnd())
	{
		nowSceneType = sceneType;
	}
}

/// <summary>
/// ��ʂ�J�ڂ���
/// </summary>
void ResultScene::ReturnScreen()
{
	if (titleFlag)
	{
		//�^�C�g����ʂ֑J��
		InputScene(SceneType::TITLE);
	}

	if (selectionFlag)
	{
		//�X�e�[�W�I����ʂ֑J��
		InputScene(SceneType::SELECTION);
	}
}

/// <summary>
/// �����̓_�ŏ���
/// </summary>
void ResultScene::Blink()
{
	if (alpha > MAX_ALPHA && inc > 0 ||
		alpha < 0 && inc < 0)
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
	backGroundY += BACKGROUND_Y_INCREASE;

	//Y���W���X�N���[���[�ɂȂ�����
	if (backGroundY == SCREEN_HEIGHT)
	{
		backGroundY = 0;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Draw()
{
	DrawGraph(backGroundX, backGroundY,  backGroundImage, TRUE);

	DrawGraph(backGroundX, backGroundY - SCREEN_HEIGHT, backGroundImage, TRUE);

	//�Q�[���N���A�Ȃ��
	if (clear)
	{
		for (auto fireWorksParticlePtr : fireWorksParticle)
		{
			fireWorksParticlePtr->Draw();
		}

		DrawFormatStringToHandle(600, 400, GetColor(255, 215, 0), fontHandle, "%s", gameClear);
	}
	//�Q�[���I�[�o�[�Ȃ��
	else
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), fontHandle, "%s", gameOver);
	}

	Blink();

	fadeManager->Draw();
}