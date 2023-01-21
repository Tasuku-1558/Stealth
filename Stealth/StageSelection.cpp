#include "StageSelection.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "FadeManager.h"


const string StageSelection::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string StageSelection::SELECTION_PATH	   = "selection.png";	//選択画像のパス

char stageName[][32] = {
	"STAGE1",
	"STAGE2",
	"TITLE",
};

StageSelection::StageSelection(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, selectionHandle(0)
	, stageNumMax(0)
	, stageNo(0)
	, fadeManager(nullptr)
	, i(0)
	, state()
	, frame(0)
{
	//処理なし
}

StageSelection::~StageSelection()
{
	Finalize();
}

void StageSelection::Initialize()
{
	string failePath = IMAGE_FOLDER_PATH + SELECTION_PATH;
	selectionHandle = LoadGraph(failePath.c_str());

	fadeManager = new FadeManager();

	stageNumMax = sizeof(stageName) / sizeof(char[32]);
}

void StageSelection::Finalize()
{
	DeleteGraph(selectionHandle);

	SafeDelete(fadeManager);
}

void StageSelection::Activate()
{
}

void StageSelection::Update(float deltaTime)
{

	//fadeManager->FadeMove();


	if (CheckHitKey(KEY_INPUT_UP))
	{

	}



	//次のシーンへ
	if (CheckHitKey(KEY_INPUT_1))
	{
		parent->SetNextScene(SceneManager::STAGE1);

	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		parent->SetNextScene(SceneManager::STAGE2);
	}
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		parent->SetNextScene(SceneManager::TITLE);
	}

	++frame;
}

int StageSelection::stageIncrement(int stageNum)
{
	if (stageNum > 0 && stageNum < stageNumMax)
	{
		return stageNum + 1;
	}

	return 1;
}

int StageSelection::stageDecrement(int stageNum)
{
	if (stageNum == 1)
	{
		return stageNumMax;
	}

	return stageNum - 1;
}

int StageSelection::StageCreator(int stageNum)
{
	if (stageNum < 0)
	{
		return NULL;
	}

	switch (state)
	{
	case StageSelection::State::STAGE1:
		parent->SetNextScene(SceneManager::STAGE1);
		break;

	case StageSelection::State::STAGE2:
		parent->SetNextScene(SceneManager::STAGE2);
		break;

	case StageSelection::State::TITLE:
		parent->SetNextScene(SceneManager::TITLE);
		break;
	}

	return NULL;
}

void StageSelection::Draw()
{
	DrawGraph(0, 0, selectionHandle, TRUE);

	for (i = 0; i < stageNumMax; i++)
	{
		DrawString(0, i * 50, stageName[i], GetColor(255, 255, 255));
	}
	
	fadeManager->Draw();
}