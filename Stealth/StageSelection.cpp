#include "StageSelection.h"

#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "SelectionUi.h"
#include "KeyManager.h"
#include "FadeManager.h"
#include "Set.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
StageSelection::StageSelection(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, stageMax(0)
	, stageNo(0)
	, light(nullptr)
	, camera(nullptr)
	, selectionUi(nullptr)
	, fadeManager(nullptr)
	, changeScene(false)
	, changeTimeCount(0)
	, maxTime(0)
	, pushCount(0.0f)
	, frame(0.0f)
	, PUSH_INTERVAL(0.2f)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
StageSelection::~StageSelection()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void StageSelection::Initialize()
{
	light = new Light();
	light->Initialize();

	camera = new Camera();
	camera->Initialize();
	
	selectionUi = new SelectionUi();
	selectionUi->Initialize();

	fadeManager = new FadeManager();

	stageMax = sizeof(char[6][32]) / sizeof(char[32]);

}

/// <summary>
/// 終了処理
/// </summary>
void StageSelection::Finalize()
{
	SafeDelete(light);

	SafeDelete(camera);

	SafeDelete(selectionUi);

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
	frame = 0.0f;
	changeScene = false;
	changeTimeCount = 0;
	maxTime = 80;
	pushCount = 0.0f;

	fadeManager->Activate();

	//フォントデータの作成
	font = CreateFontToHandle("Oranienbaum", 120, 1);
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
/// 各シーンへ遷移
/// </summary>
/// <param name="stageNumber"></param>
/// <returns></returns>
int StageSelection::StageCreator(int stageNumber)
{
	if (stageNumber < 0)
	{
		return NULL;
	}

	//各シーン
	if (stageNumber == 1)
	{
		parent->SetNextScene(SceneManager::STAGE1);
	}
	if (stageNumber == 6)
	{
		parent->SetNextScene(SceneManager::TITLE);
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void StageSelection::Update(float deltaTime)
{
	camera->SelectionAndResultCamera();

	KeyMove(deltaTime);
}

/// <summary>
/// キー操作
/// </summary>
/// <param name="deltaTime"></param>
void StageSelection::KeyMove(float deltaTime)
{
	pushCount -= deltaTime;

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

	//リターンキーを押したならば
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_RETURN))
	{
		changeScene = true;
	}

	//リターンキーを押したならば
	if (changeScene)
	{
		changeTimeCount++;

		frame += deltaTime;

		if (changeTimeCount > maxTime)
		{
			//画面効果処理を行う
			fadeManager->FadeMove();

			//フレームが3.5秒経過したら画面を遷移する
			if (frame > 3.5f)
			{
				StageCreator(stageNo);
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
	else if (stageNo == 6)
	{
		selectionUi->TitleUiDraw();
	}

	if (!changeScene || (changeTimeCount / 5) % 2 == 0)
	{
		DrawFormatStringToHandle(200, 250, GetColor(0, 255, 0), font, "STAGE : %d", stageNo);
	}
	
	selectionUi->Draw();

	fadeManager->Draw();
}