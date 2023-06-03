#include "StageSelection.h"

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
	, fadeCount(0.0f)
	, changeScene(false)
	, MAX_STAGE(6)
	, FIRST_STAGE_NUMBER(1)
	, SECOND_STAGE_NUMBER(2)
	, THIRD_STAGE_NUMBER(3)
	, FOURTH_STAGE_NUMBER(4)
	, FIFTH_STAGE_NUMBER(5)
	, TITLE_RETURN_NUMBER(6)
	, ADD_STAGE_NUMBER(1)
	, SELECTION_FONT_SIZE(120)
	, FONT_THICK(1)
	, MAX_PUSH_COUNT(0.0f)
	, PUSH_INTERVAL(0.2f)
	, FADE_START_COUNT(1.0f)
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

	return ADD_STAGE_NUMBER;
}

/// <summary>
/// 選択ステージを1つ前に持っていく
/// </summary>
/// <param name="stageNumber">ステージの番号</param>
/// <returns>ステージの番号を返す</returns>
int StageSelection::stageDecrement(int stageNumber)
{
	//最初のステージに来た時
	if (stageNumber == FIRST_STAGE_NUMBER)
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
	//ステージの番号がタイトルの数ではなかったら
	if (stageNumber != TITLE_RETURN_NUMBER)
	{
		nowSceneType = SceneType::GAME;
	}
	else
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
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_UP) && pushCount < MAX_PUSH_COUNT)
		{
			stageNo = stageDecrement(stageNo);
			pushCount = PUSH_INTERVAL;
		}
		if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_DOWN) && pushCount < MAX_PUSH_COUNT)
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

		fadeCount += deltaTime;

		//1秒経過したら
		if (fadeCount > FADE_START_COUNT)
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
	//ステージの番号、敵の数、ケーキの数を入力
	StageUi stageUi[] =
	{
		{FIRST_STAGE_NUMBER, 1, 1},
		{SECOND_STAGE_NUMBER, 2, 2},
		{THIRD_STAGE_NUMBER, 4, 2},
		{FOURTH_STAGE_NUMBER, 3, 1},
		{FIFTH_STAGE_NUMBER, 4, 1},
	};

	for (int i = 0; i < MAX_STAGE_NUMBER; i++)
	{
		if (stageNo == stageUi[i].number)
		{
			selectionUi->StageUiDraw(stageUi[i].enemyNumber, stageUi[i].cakeNumber);
		}
	}

	if (stageNo == TITLE_RETURN_NUMBER)
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