#include "StageSelection.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "FadeManager.h"


const string StageSelection::IMAGE_FOLDER_PATH = "data/image/";						//imageフォルダまでのパス
const string StageSelection::SELECTION_PATH	   = "selection.png";					//選択画像のパス
const string StageSelection::STAGE1_MAP_PATH   = "stage1_map.png";					//ステージ1マップの画像のパス
const string StageSelection::STAGE1_DESCRIPTION_PAHT = "stage1_description.png";	//ステージ1の説明画像のパス
const string StageSelection::STAGE2_MAP_PATH = "stage2_map.png";					//ステージ2マップの画像のパス
const string StageSelection::STAGE2_DESCRIPTION_PAHT = "stage2_description.png";	//ステージ2の説明画像のパス


char stageName[][32] = {
	"STAGE1",
	"STAGE2",
	"TITLE",
};

StageSelection::StageSelection(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, selectionHandle(0)
	, stage1MapHandle(0)
	, stage1Description(0)
	, stage2MapHandle(0)
	, stage2Description(0)
	, stageMax(0)
	, stageNo(1)
	, fadeManager(nullptr)
	, changeScene(false)
	, changeTimeCount(0)
	, maxTime(80)
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

	failePath = IMAGE_FOLDER_PATH + STAGE1_MAP_PATH;
	stage1MapHandle = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + STAGE1_DESCRIPTION_PAHT;
	stage1Description = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + STAGE2_MAP_PATH;
	stage2MapHandle = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + STAGE2_DESCRIPTION_PAHT;
	stage2Description = LoadGraph(failePath.c_str());

	fadeManager = new FadeManager();

	stageMax = sizeof(stageName) / sizeof(char[32]);
}

void StageSelection::Finalize()
{
	DeleteGraph(selectionHandle);

	DeleteGraph(stage1MapHandle);
	DeleteGraph(stage1Description);

	DeleteGraph(stage2MapHandle);
	DeleteGraph(stage2Description);

	SafeDelete(fadeManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

void StageSelection::Activate()
{
	stageNo = 1;
	changeScene = false;
	changeTimeCount = 0;

	font = CreateFontToHandle("Oranienbaum", 120, 1);
}

/// <summary>
/// 選択ステージを1個前に
/// </summary>
/// <param name="stageNum"></param>
/// <returns></returns>
int StageSelection::stageDecrement(int stageNum)
{
	//最初のステージに来た時
	if (stageNum == 1)
	{
		return stageMax;
	}

	return stageNum - 1;
}

/// <summary>
/// 選択ステージを1個先に
/// </summary>
/// <param name="stageNum"></param>
/// <returns></returns>
int StageSelection::stageIncrement(int stageNum)
{
	if (stageNum > 0 && stageNum < stageMax)
	{
		return stageNum + 1;
	}

	return 1;
}

int StageSelection::StageCreator(int stageNum)
{
	if (stageNum < 0)
	{
		return NULL;
	}

	//各シーン
	switch (stageNum)
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

void StageSelection::Update(float deltaTime)
{

	//fadeManager->FadeMove();

	//キー操作
	if (CheckHitKey(KEY_INPUT_UP))
	{
		stageNo = stageDecrement(stageNo);
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		stageNo = stageIncrement(stageNo);
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		changeScene = true;
	}

	//リターンキーを押したならば
	if (changeScene)
	{
		changeTimeCount++;

		if (changeTimeCount > maxTime)
		{
			StageCreator(stageNo);
		}
	}
	
	//次のシーンへ
	/*if (CheckHitKey(KEY_INPUT_1))
	{
		parent->SetNextScene(SceneManager::STAGE1);
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		parent->SetNextScene(SceneManager::STAGE2);
	}*/
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		parent->SetNextScene(SceneManager::TITLE);
	}

}

void StageSelection::Draw()
{
	DrawGraph(0, 0, selectionHandle, TRUE);

	if (stageNo == 1)
	{
		DrawGraph(1100, 400, stage1MapHandle, TRUE);
		DrawGraph(100, 400, stage1Description, TRUE);
	}
	else if (stageNo == 2)
	{
		DrawGraph(1100, 400, stage2MapHandle, TRUE);
		DrawGraph(100, 400, stage2Description, TRUE);
	}

	if (!changeScene || (changeTimeCount / 5) % 2 == 0)
	{
		DrawFormatStringToHandle(750, 250, GetColor(0, 255, 0), font, "STAGE : %d", stageNo);
	}
	
	fadeManager->Draw();
}