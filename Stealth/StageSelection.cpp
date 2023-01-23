#include "StageSelection.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "FadeManager.h"


const string StageSelection::IMAGE_FOLDER_PATH = "data/image/";						//image�t�H���_�܂ł̃p�X
const string StageSelection::SELECTION_PATH	   = "selection.png";					//�I���摜�̃p�X
const string StageSelection::STAGE1_MAP_PATH   = "stage1_map.png";					//�X�e�[�W1�}�b�v�̉摜�̃p�X
const string StageSelection::STAGE2_MAP_PATH   = "stage2_map.png";					//�X�e�[�W2�}�b�v�̉摜�̃p�X
const string StageSelection::STAGE1_DESCRIPTION_PAHT = "stage1_description.png";	//�X�e�[�W1�̐����摜�̃p�X
const string StageSelection::STAGE2_DESCRIPTION_PAHT = "stage2_description.png";	//�X�e�[�W2�̐����摜�̃p�X
const int	 StageSelection::STAGE_IMAGE_NUMBER		 = 2;							//�X�e�[�W�摜��


char stageName[][32] = {
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
	, selectionHandle(0)
	, stageMapHandle()
	, stageDescription()
	, stageMax(0)
	, stageNo(1)
	, fadeManager(nullptr)
	, changeScene(false)
	, changeTimeCount(0)
	, maxTime(80)
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
	string failePath = IMAGE_FOLDER_PATH + SELECTION_PATH;
	selectionHandle = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + STAGE1_MAP_PATH;
	stageMapHandle[0] = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + STAGE1_DESCRIPTION_PAHT;
	stageDescription[0] = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + STAGE2_MAP_PATH;
	stageMapHandle[1] = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + STAGE2_DESCRIPTION_PAHT;
	stageDescription[1] = LoadGraph(failePath.c_str());

	fadeManager = new FadeManager();

	stageMax = sizeof(stageName) / sizeof(char[32]);
}

/// <summary>
/// �I������
/// </summary>
void StageSelection::Finalize()
{
	DeleteGraph(selectionHandle);

	for (int i = 0; i < STAGE_IMAGE_NUMBER; i++)
	{
		DeleteGraph(stageMapHandle[i]);
		DeleteGraph(stageDescription[i]);
	}

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

	//�L�[����
	if (CheckHitKey(KEY_INPUT_UP))
	{
		stageNo = stageDecrement(stageNo);
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		stageNo = stageIncrement(stageNo);
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
	DrawGraph(0, 0, selectionHandle, TRUE);

	if (stageNo == 1)
	{
		DrawGraph(1100, 400, stageMapHandle[0], TRUE);
		DrawGraph(100, 400, stageDescription[0], TRUE);
	}
	else if (stageNo == 2)
	{
		DrawGraph(1100, 400, stageMapHandle[1], TRUE);
		DrawGraph(100, 400, stageDescription[1], TRUE);
	}

	if (!changeScene || (changeTimeCount / 5) % 2 == 0)
	{
		DrawFormatStringToHandle(750, 250, GetColor(0, 255, 0), font, "STAGE : %d", stageNo);
	}
	
	fadeManager->Draw();
}