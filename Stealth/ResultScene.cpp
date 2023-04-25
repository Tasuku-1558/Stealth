#include "ResultScene.h"
#include "PreCompiledHeader.h"
#include "Camera.h"
#include "FireWorksParticle.h"
#include "FadeManager.h"
#include "KeyManager.h"
#include "InputManager.h"
#include "Set.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultScene::ResultScene()
	: SceneBase(SceneType::RESULT)
	, resultFontHandle(0)
	, resultUiImage(0)
	, alpha(255)
	, inc(-3)
	, backGroundImage(0)
	, backGroundPosY(0)
	, frame(0.0f)
	, fireWorksParticle()
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(false)
	, titleFlag(false)
	, selectionFlag(false)
	, RESULT_FONT_SIZE(150)
	, FONT_THICK(1)
	, PARTICLE_NUMBER(500)
	, MAX_ALPHA(255)
	, INC_SPEED(-1)
	, RESULT_UI_POS_X(1500)
	, RESULT_UI_POS_Y(1000)
	, BACKGROUND_POS_X(0)
	, BACKGROUND_Y_INCREASE(2)
	, INITIAL_BACKGROUND_POS_Y(0)
	, RESULT_STRING_POS_X(600)
	, RESULT_STRING_POS_Y(400)
	, GAME_CLEAR_COLOR(GetColor(255, 215, 0))
	, GAME_OVER_COLOR(GetColor(255, 0, 0))
	, MAX_PARTICLE_INTERVAL(2.0f)
	, PARTICLE_INTERVAL(0.0f)
	, RESULT_UI_SIZE(0.5)
	, RESULT_UI_ANGLE(0.0)
	, GAME_CLEAR("GAME CLEAR")
	, GAME_OVER("GAME OVER")
	, IMAGE_FOLDER_PATH("Data/Image/")
	, RESULT_UI_PATH("resultUi.png")
	, RESULT_BACKGROUND_PATH("resultBackGround.png")
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
	DeleteFontToHandle(resultFontHandle);
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Initialize()
{
	camera = new Camera();

	fadeManager = new FadeManager();

	//���U���gUi�摜�̓ǂݍ���
	resultUiImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	backGroundImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, RESULT_BACKGROUND_PATH).c_str());

	//�Q�[�����N���A�������ǂ������i�[����
	clear = Set::GetInstance().GetResult();

	//�t�H���g�f�[�^�̓ǂݍ���
	resultFontHandle = CreateFontToHandle("Oranienbaum", RESULT_FONT_SIZE, FONT_THICK);
}

/// <summary>
/// �ԉ΃p�[�e�B�N����o�^
/// </summary>
/// <param name="newFireWorksParticle">�o�^����ԉ΃p�[�e�B�N���̃|�C���^</param>
void ResultScene::EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle)
{
	fireWorksParticle.emplace_back(newFireWorksParticle);
}

/// <summary>
/// �ԉ΃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteFireWorksParticle">�폜����ԉ΃p�[�e�B�N���̃|�C���^</param>
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
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
SceneType ResultScene::Update(float deltaTime)
{
	camera->SelectionAndResultCamera();

	BackGroundMove();

	FireWorksParticlePop();
	
	//�p�[�e�B�N�����o������
	if (particleFlag)
	{
		particleInterval += deltaTime;
	
		//2�b�o�߂�����
		//�p�[�e�B�N�����ēx�o����悤�ɂ���
		if (particleInterval > MAX_PARTICLE_INTERVAL)
		{
			particleFlag = false;
			particleInterval = PARTICLE_INTERVAL;
		}
	}
	
	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Update(deltaTime);
	}
	
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
/// <param name="sceneType">�V�[���̎��</param>
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
		inc *= INC_SPEED;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawRotaGraph(RESULT_UI_POS_X, RESULT_UI_POS_Y, RESULT_UI_SIZE, RESULT_UI_ANGLE, resultUiImage, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// �w�i�摜�̓���
/// </summary>
void ResultScene::BackGroundMove()
{
	backGroundPosY += BACKGROUND_Y_INCREASE;

	//�w�i�摜��Y���W���X�N���[���̒[�ɂ�������
	if (backGroundPosY == SCREEN_HEIGHT)
	{
		backGroundPosY = INITIAL_BACKGROUND_POS_Y;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Draw()
{
	DrawGraph(BACKGROUND_POS_X, backGroundPosY,  backGroundImage, TRUE);

	DrawGraph(BACKGROUND_POS_X, backGroundPosY - SCREEN_HEIGHT, backGroundImage, TRUE);

	//�Q�[���N���A�Ȃ��
	if (clear)
	{
		for (auto fireWorksParticlePtr : fireWorksParticle)
		{
			fireWorksParticlePtr->Draw();
		}

		DrawFormatStringToHandle(RESULT_STRING_POS_X, RESULT_STRING_POS_Y, GAME_CLEAR_COLOR, resultFontHandle, "%s", GAME_CLEAR);
	}
	//�Q�[���I�[�o�[�Ȃ��
	else
	{
		DrawFormatStringToHandle(RESULT_STRING_POS_X, RESULT_STRING_POS_Y, GAME_OVER_COLOR, resultFontHandle, "%s", GAME_OVER);
	}

	Blink();

	fadeManager->Draw();
}