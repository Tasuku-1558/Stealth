#include "StageSelection.h"
#include "DxLib.h"


const string StageSelection::IMAGE_FOLDER_PATH = "data/image/";		//image�t�H���_�܂ł̃p�X
const string StageSelection::SELECTION_PATH	   = "selection.png";	//�I���摜�̃p�X

char stageName[][32] = {
	"STAGE1",
	"STAGE2",
};

StageSelection::StageSelection(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, selectionHandle(0)
	, stageNumMax(2)
{
	//�����Ȃ�
}

StageSelection::~StageSelection()
{
	Finalize();
}

void StageSelection::Initialize()
{
	string failePath = IMAGE_FOLDER_PATH + SELECTION_PATH;
	selectionHandle = LoadGraph(failePath.c_str());
}

void StageSelection::Finalize()
{
	DeleteGraph(selectionHandle);
}

void StageSelection::Activate()
{
}

void StageSelection::Update(float deltaTime)
{
	scene = SceneManager::STAGE1;

	//���̃V�[����
	if (CheckHitKey(KEY_INPUT_1))
	{
		parent->SetNextScene(SceneManager::STAGE1);
		return;
	}
	else if (CheckHitKey(KEY_INPUT_2))
	{
		parent->SetNextScene(SceneManager::STAGE2);
		return;
	}
	else if (CheckHitKey(KEY_INPUT_BACK))
	{
		parent->SetNextScene(SceneManager::TITLE);
		return;
	}
}

SceneManager* StageSelection::StageCreator(int stageNum)
{
	if (stageNum < 0)
	{
		return NULL;
	}
	
	switch (scene)
	{
	case SceneManager::TITLE:
		break;
	case SceneManager::SELECTION:
		break;
	case SceneManager::STAGE1:
		break;
	case SceneManager::STAGE2:
		parent->SetNextScene(SceneManager::STAGE2);
		return 0;
		break;
	
	}

	return NULL;
}

int StageSelection::StageDecrement(int stageNum)
{
	//�ŏ��̃X�e�[�W�ɗ�����
	if (stageNum == 1)
	{
		return stageNumMax;
	}

	//����ȊO�̂Ƃ�
	return stageNum - 1;
}

int StageSelection::StageIncrement(int stageNum)
{

	// �X�e�[�W�Z���N�g���͈͓��̎�
	if (stageNum > 0 && stageNum < stageNumMax)
	{
		return stageNum + 1;
	}

	//�Ō�̃X�e�[�W�܂ŗ����Ƃ�
	return 1;
}

void StageSelection::Draw()
{
	DrawGraph(0, 0, selectionHandle, TRUE);
}