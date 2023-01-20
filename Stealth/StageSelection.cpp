#include "StageSelection.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "FadeManager.h"


const string StageSelection::IMAGE_FOLDER_PATH = "data/image/";		//imageフォルダまでのパス
const string StageSelection::SELECTION_PATH	   = "selection.png";	//選択画像のパス

char stageName[][32] = {
	"STAGE1",
	"STAGE2",
};

StageSelection::StageSelection(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, selectionHandle(0)
	, stageNumMax(2)
	, fadeManager(nullptr)
	, i(0)
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
	//scene = SceneManager::STAGE2;
	
	//fadeManager->FadeMove();

	if (CheckHitKey(KEY_INPUT_UP))
	{
		i++;
		
	}

	//次のシーンへ
	if (CheckHitKey(KEY_INPUT_1))
	{
		//if (fadeManager->Fade() < 5)
		{
			parent->SetNextScene(SceneManager::STAGE1);
		}
		
	}
	else if (CheckHitKey(KEY_INPUT_2))
	{
		parent->SetNextScene(SceneManager::STAGE2);
	}
	else if (CheckHitKey(KEY_INPUT_BACK))
	{
		parent->SetNextScene(SceneManager::TITLE);
	}
}

void StageSelection::StageCreator()
{
	
	switch (scene)
	{
	case SceneManager::TITLE:
		break;
	case SceneManager::SELECTION:
		break;
	case SceneManager::STAGE1:
		break;
	case SceneManager::STAGE2:

		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			parent->SetNextScene(SceneManager::STAGE2);
		}
		
		break;
	
	}

}

void StageSelection::Draw()
{
	DrawGraph(0, 0, selectionHandle, TRUE);

	for (i = 0; i < 2; i++)
	{
		DrawString(0, i * 50, stageName[i], GetColor(255, 255, 255));
	}
	
	//fadeManager->Draw();
}