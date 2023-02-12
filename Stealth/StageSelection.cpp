#include "StageSelection.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "SelectionUi.h"
#include "FadeManager.h"


const float StageSelection::PUSH_INTERVAL = 0.2f;		//�؂�ւ��J�E���g�̃C���^�[�o��


char stageName[][32] =
{
	"STAGE1",
	"STAGE2",
	"STAGE3",
	"TITLE",
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
StageSelection::StageSelection(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, stageMax(0)
	, stageNo(0)
	, light(nullptr)
	, selectionUi(nullptr)
	, fadeManager(nullptr)
	, changeScene(false)
	, changeTimeCount(0)
	, maxTime(0)
	, pushCount(0.0f)
	, frame(0.0f)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageSelection::~StageSelection()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void StageSelection::Initialize()
{
	light = new Light();
	
	selectionUi = new SelectionUi();
	selectionUi->Initialize();

	fadeManager = new FadeManager();

	stageMax = sizeof(stageName) / sizeof(char[32]);

}

/// <summary>
/// �I������
/// </summary>
void StageSelection::Finalize()
{
	SafeDelete(light);

	SafeDelete(selectionUi);

	SafeDelete(fadeManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void StageSelection::Activate()
{
	stageNo = 1;
	frame = 0.0f;
	changeScene = false;
	changeTimeCount = 0;
	maxTime = 80;
	pushCount = 0.0f;

	selectionUi->Activate();

	fadeManager->Activate();

	//�t�H���g�f�[�^�̍쐬
	font = CreateFontToHandle("Oranienbaum", 120, 1);
}

/// <summary>
/// �I���X�e�[�W��1��Ɏ����Ă���
/// </summary>
/// <param name="stageNum"></param>
/// <returns></returns>
int StageSelection::stageIncrement(int stageNumber)
{
	if (stageNumber > 0 && stageNumber < stageMax)
	{
		return stageNumber + 1;
	}

	return 1;
}

/// <summary>
/// �I���X�e�[�W��1�O�Ɏ����Ă���
/// </summary>
/// <param name="stageNum"></param>
/// <returns></returns>
int StageSelection::stageDecrement(int stageNumber)
{
	//�ŏ��̃X�e�[�W�ɗ�����
	if (stageNumber == 1)
	{
		return stageMax;
	}

	return stageNumber - 1;
}

/// <summary>
/// �e�V�[���֑J��
/// </summary>
/// <param name="stageNumber"></param>
/// <returns></returns>
int StageSelection::StageCreator(int stageNumber)
{
	if (stageNumber < 0)
	{
		return NULL;
	}

	//�e�V�[��
	switch (stageNumber)
	{
	case 1:
		parent->SetNextScene(SceneManager::STAGE1);
		break;

	case 2:
		parent->SetNextScene(SceneManager::STAGE2);
		break;

	case 3:
		parent->SetNextScene(SceneManager::STAGE3);
		break;

	case 4:
		parent->SetNextScene(SceneManager::TITLE);
		break;
	}

	return NULL;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void StageSelection::Update(float deltaTime)
{
	//�Z���N�V������ʂł̃��C�g�̕����̐ݒ�
	light->Update({ 0.0f, 0.0f, 0.5f });

	KeyMove(deltaTime);
}

/// <summary>
/// �L�[����
/// </summary>
/// <param name="deltaTime"></param>
void StageSelection::KeyMove(float deltaTime)
{
	pushCount -= deltaTime;

	//�L�[����
	if (CheckHitKey(KEY_INPUT_UP) && pushCount < 0.0f)
	{
		stageNo = stageDecrement(stageNo);
		pushCount = PUSH_INTERVAL;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) && pushCount < 0.0f)
	{
		stageNo = stageIncrement(stageNo);
		pushCount = PUSH_INTERVAL;
	}

	//���^�[���L�[���������Ȃ��
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		changeScene = true;
	}

	//���^�[���L�[���������Ȃ��
	if (changeScene)
	{
		changeTimeCount++;

		frame += deltaTime;

		if (changeTimeCount > maxTime)
		{
			//��ʌ��ʏ������s��
			fadeManager->FadeMove();

			//�t���[����3.5�b�o�߂������ʂ�J�ڂ���
			if (frame > 3.5f)
			{
				StageCreator(stageNo);
			}
		}
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void StageSelection::Draw()
{
	//���ꂼ��̃X�e�[�W���Ƃ�UI�`�揈��
	if (stageNo == 1)
	{
		selectionUi->StageUiDraw(0);
	}
	else if (stageNo == 2)
	{
		selectionUi->StageUiDraw(1);
	}
	else if (stageNo == 3)
	{
		selectionUi->StageUiDraw(2);
	}
	else if (stageNo == 4)
	{
		selectionUi->TitleUiDraw();
	}

	if (!changeScene || (changeTimeCount / 5) % 2 == 0)
	{
		DrawFormatStringToHandle(200, 250, GetColor(0, 255, 0), font, "STAGE : %d", stageNo);
	}
	
	selectionUi->Draw();

	fadeManager->Draw();
}