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
	, stageNo(1)
	, light(nullptr)
	, selectionUi(nullptr)
	, fadeManager(nullptr)
	, changeScene(false)
	, changeTimeCount(0)
	, maxTime(80)
	, pushCount(0.0f)
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
	selectionUi->Finalize();

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
	changeScene = false;
	changeTimeCount = 0;

	selectionUi->Activate();

	font = CreateFontToHandle("Oranienbaum", 120, 1);
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
	//fadeManager->FadeMove();
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
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		parent->SetNextScene(SceneManager::TITLE);
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		changeScene = true;
	}

	//���^�[���L�[���������Ȃ��
	if (changeScene)
	{
		changeTimeCount++;

		if (changeTimeCount > maxTime)
		{
			StageCreator(stageNo);
		}
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void StageSelection::Draw()
{

	if (stageNo == 1)
	{
		selectionUi->Stage1_Draw();
	}
	else if (stageNo == 2)
	{
		selectionUi->Stage2_Draw();
	}

	if (!changeScene || (changeTimeCount / 5) % 2 == 0)
	{
		DrawFormatStringToHandle(200, 250, GetColor(0, 255, 0), font, "STAGE : %d", stageNo);
	}
	
	selectionUi->Draw();

	fadeManager->Draw();
}