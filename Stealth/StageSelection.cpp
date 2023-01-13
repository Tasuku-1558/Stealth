#include "StageSelection.h"
#include "DxLib.h"


const string StageSelection::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string StageSelection::SELECTION_PATH	   = "selection.png";	//選択画像のパス


StageSelection::StageSelection(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, selectionHandle(0)
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
	//次のシーンへ
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

void StageSelection::Draw()
{
	DrawGraph(0, 0, selectionHandle, TRUE);
}