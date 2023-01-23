#include "StageSelection.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "FadeManager.h"


const string StageSelection::IMAGE_FOLDER_PATH = "data/image/";						//imageフォルダまでのパス
const string StageSelection::SELECTION_PATH	   = "selection.png";					//選択画像のパス
const string StageSelection::STAGE1_MAP_PATH   = "stage1_map.png";					//ステージ1マップの画像のパス
const string StageSelection::STAGE2_MAP_PATH   = "stage2_map.png";					//ステージ2マップの画像のパス
const string StageSelection::STAGE1_DESCRIPTION_PAHT = "stage1_description.png";	//ステージ1の説明画像のパス
const string StageSelection::STAGE2_DESCRIPTION_PAHT = "stage2_description.png";	//ステージ2の説明画像のパス
const int	 StageSelection::STAGE_IMAGE_NUMBER		 = 2;							//ステージ画像数


char stageName[][32] = {
	"STAGE1",
	"STAGE2",
	"TITLE",
};

/// <summary>
/// コンストラクタ
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
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
StageSelection::~StageSelection()
{
	Finalize();
}

/// <summary>
/// 初期化処理
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
/// 終了処理
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

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 活性化処理
/// </summary>
void StageSelection::Activate()
{
	stageNo = 1;
	changeScene = false;
	changeTimeCount = 0;

	font = CreateFontToHandle("Oranienbaum", 120, 1);
}

/// <summary>
/// 選択ステージを1個前に持っていく
/// </summary>
/// <param name="stageNum"></param>
/// <returns></returns>
int StageSelection::stageDecrement(int stageNumber)
{
	//最初のステージに来た時
	if (stageNumber == 1)
	{
		return stageMax;
	}

	return stageNumber - 1;
}

/// <summary>
/// 選択ステージを1個先に持っていく
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

	//各シーン
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
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
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
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		parent->SetNextScene(SceneManager::TITLE);
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
}

/// <summary>
/// 描画処理
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