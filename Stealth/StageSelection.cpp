#include "StageSelection.h"

#include "PreCompiledHeader.h"
#include "Camera.h"
#include "SelectionUi.h"
#include "KeyManager.h"
#include "FadeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
StageSelection::StageSelection()
	: SceneBase(SceneType::SELECTION)
	, fontHandle(0)
	, stageMax(0)
	, stageNo(0)
	, changeTimeCount(0)
	, pushCount(0.0f)
	, frame(0.0f)
	, changeScene(false)
	, STAGE_NUMBER(6)
	, MAX_TIME(80)
	, FIRST_STAGE_NUMBER(1)
	, PUSH_INTERVAL(0.2f)
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
StageSelection::~StageSelection()
{
	DeleteFontToHandle(fontHandle);
}

/// <summary>
/// 初期化処理
/// </summary>
void StageSelection::Initialize()
{
	camera = new Camera();
	
	selectionUi = new SelectionUi();

	fadeManager = new FadeManager();

	stageNo = FIRST_STAGE_NUMBER;

	stageMax = STAGE_NUMBER;

	//フォントデータの作成
	fontHandle = CreateFontToHandle("Oranienbaum", 120, 1);
}

/// <summary>
/// 選択ステージを1つ先に持っていく
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
/// 選択ステージを1つ前に持っていく
/// </summary>
/// <param name="stageNumber"></param>
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
/// 各シーンへ遷移
/// </summary>
/// <param name="stageNumber"></param>
void StageSelection::StageCreator(int stageNumber)
{
	//各シーン
	if (stageNumber == 1)
	{
		nowSceneType = SceneType::GAME;
	}
	if (stageNumber == 2)
	{
		nowSceneType = SceneType::GAME;
	}
	if (stageNumber == 6)
	{
		nowSceneType = SceneType::TITLE;
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
SceneType StageSelection::Update(float deltaTime)
{
	camera->SelectionAndResultCamera();

	KeyMove(deltaTime);

	return nowSceneType;
}

/// <summary>
/// キー操作
/// </summary>
/// <param name="deltaTime"></param>
void StageSelection::KeyMove(float deltaTime)
{
	pushCount -= deltaTime;

	//リターンキーを押していないならばキーの操作を有効にする
	if (!changeScene)
	{
		//矢印キー操作
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP) && pushCount < 0.0f)
		{
			stageNo = stageDecrement(stageNo);
			pushCount = PUSH_INTERVAL;
		}
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_DOWN) && pushCount < 0.0f)
		{
			stageNo = stageIncrement(stageNo);
			pushCount = PUSH_INTERVAL;
		}
	}

	//リターンキーを押したならば
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RETURN))
	{
		changeScene = true;
	}

	//リターンキーを押したならば
	if (changeScene)
	{
		//文字点滅カウントを開始する
		changeTimeCount++;

		frame += deltaTime;

		//1秒経過したら
		if (frame > 1.0f)
		{
			fadeManager->FadeMove();

			//フェードが終わったら
			if (fadeManager->FadeEnd())
			{
				StageCreator(stageNo);
			}
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void StageSelection::Draw()
{
	//それぞれのステージごとのUI描画処理
	//マップの番号、敵の数、ケーキの数を入力
	if (stageNo == 1)
	{
		selectionUi->StageUiDraw(0, 1, 1);
	}
	else if (stageNo == 2)
	{
		selectionUi->StageUiDraw(1, 2, 2);
	}
	else if (stageNo == 3)
	{
		selectionUi->StageUiDraw(2, 4, 2);
	}
	else if (stageNo == 4)
	{
		selectionUi->StageUiDraw(3, 3, 1);
	}
	else if (stageNo == 5)
	{
		selectionUi->StageUiDraw(4, 4, 1);
	}
	else if (stageNo == 6)
	{
		selectionUi->TitleUiDraw();
	}

	if ((changeTimeCount / 5) % 2 == 0)
	{
		DrawFormatStringToHandle(200, 250, GetColor(0, 255, 0), fontHandle, "STAGE : %d", stageNo);
	}
	
	selectionUi->Draw();

	fadeManager->Draw();
}