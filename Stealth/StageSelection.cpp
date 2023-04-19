#include "StageSelection.h"

#include "PreCompiledHeader.h"
#include "Camera.h"
#include "SelectionUi.h"
#include "KeyManager.h"
#include "FadeManager.h"
#include "Set.h"

/// <summary>
/// コンストラクタ
/// </summary>
StageSelection::StageSelection()
	: SceneBase(SceneType::SELECTION)
	, fontHandle(0)
	, stageNo(1)
	, changeTimeCount(0)
	, pushCount(0.0f)
	, frame(0.0f)
	, changeScene(false)
	, MAX_STAGE(6)
	, ADD_STAGE_NUMBER(1)
	, SELECTION_FONT_SIZE(120)
	, FONT_THICK(1)
	, PUSH_INTERVAL(0.2f)
	, FADE_START_FRAME(1.0f)
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

	//フォントデータの作成
	fontHandle = CreateFontToHandle("Oranienbaum", SELECTION_FONT_SIZE, FONT_THICK);
}

/// <summary>
/// 選択ステージを1つ先に持っていく
/// </summary>
/// <param name="stageNum">ステージの番号</param>
/// <returns>ステージの番号を返す</returns>
int StageSelection::stageIncrement(int stageNumber)
{
	if (stageNumber > 0 && stageNumber < MAX_STAGE)
	{
		return stageNumber + ADD_STAGE_NUMBER;
	}

	return 1;
}

/// <summary>
/// 選択ステージを1つ前に持っていく
/// </summary>
/// <param name="stageNumber">ステージの番号</param>
/// <returns>ステージの番号を返す</returns>
int StageSelection::stageDecrement(int stageNumber)
{
	//最初のステージに来た時
	if (stageNumber == 1)
	{
		return MAX_STAGE;
	}

	return stageNumber - ADD_STAGE_NUMBER;
}

/// <summary>
/// 各シーンへ遷移
/// </summary>
/// <param name="stageNumber">ステージの番号</param>
/// <returns>ステージの番号を返す</returns>
int StageSelection::StageCreator(int stageNumber)
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

	return stageNumber;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
/// <returns>今のシーンを返す</returns>
SceneType StageSelection::Update(float deltaTime)
{
	camera->SelectionAndResultCamera();

	KeyMove(deltaTime);

	return nowSceneType;
}

/// <summary>
/// キー操作
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
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
		if (frame > FADE_START_FRAME)
		{
			fadeManager->FadeMove();

			//フェードが終わったら
			if (fadeManager->FadeEnd())
			{
				stageNo = StageCreator(stageNo);
				Set::GetInstance().SetStage(stageNo);
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
	if (stageNo == 6)
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