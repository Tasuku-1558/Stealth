#include "UiManager.h"

using std::string;

const string UiManager::IMAGE_FOLDER_PATH  = "data/image/";		//画像ファイルのパス
const string UiManager::UI_GRAPHIC_PATH    = "ui";				//UI画像
const string UiManager::FILENAME_EXTENSION = ".png";			//画像拡張子


/// <summary>
/// コンストラクタ
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, count(0)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
UiManager::~UiManager()
{
	//終了処理が呼ばれてなければ
	if (uiHandle[0] != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void UiManager::Initialize()
{
	//UI画像読み込み
	string failePath = IMAGE_FOLDER_PATH + UI_GRAPHIC_PATH;		// フォルダパス + ファイル名
	string fullPath = failePath;
	
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		fullPath = failePath + std::to_string(i) + FILENAME_EXTENSION;
		uiHandle[i] = LoadGraph(fullPath.c_str());

		if (uiHandle[i] < 0)
		{
			printfDx("画像読み込みに失敗[%d]\n", i);
		}
	}
}

/// <summary>
/// 活性化処理
/// </summary>
void UiManager::Activate()
{
	count = 0;
}

/// <summary>
/// 終了処理
/// </summary>
void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}
}

/// <summary>
/// FirstStage描画処理
/// </summary>
/// <param name="state"></param>
/// <param name="playerCount"></param>
/// <param name="hitUi"></param>
void UiManager::Draw(FirstStage::State state, int playerCount, bool hitUi)
{
	//吹き出し画像描画
	DrawBillboard3D(VGet(-800.0f, 0.0f, 0.0f), 0.5f, 0.5f, 200.0f, 0.0f, uiHandle[BALLOON], TRUE);

	switch (state)
	{
	case FirstStage::State::START:
		
		break;

	case FirstStage::State::GAME:
		StartGameDraw();
		PlayerHpDraw(playerCount);
		OperationMethodDraw(hitUi);
		DrawGraph(0, 900, uiHandle[KEY], TRUE);
		break;

	case FirstStage::State::GOAL:
		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
		break;
	}
}

/// <summary>
/// SecondStage描画処理
/// </summary>
/// <param name="state"></param>
/// <param name="playerCount"></param>
void UiManager::Draw(SecondStage::State state, int playerCount)
{
	switch (state)
	{
	case SecondStage::State::START:
		
		break;

	case SecondStage::State::GAME:
		count++;

		if (count < 50)
		{
			DrawGraph(0, -50, uiHandle[STAGE2], TRUE);
		}
		PlayerHpDraw(playerCount);
		DrawGraph(0, 900, uiHandle[KEY], TRUE);
		break;

	case SecondStage::State::GOAL:
		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
		break;
	}
}

/// <summary>
/// ゲーム開始UI
/// </summary>
void UiManager::StartGameDraw()
{
	count++;

	if (count < 50)
	{
		DrawGraph(0, -50, uiHandle[STAGE1], TRUE);
	}
}

/// <summary>
/// 操作方法説明UI
/// </summary>
/// <param name="hitChecker"></param>
void UiManager::OperationMethodDraw(bool hitUi)
{
	if (hitUi)
	{
		DrawGraph(0, 20, uiHandle[OPERATION], TRUE);
	}
}

/// <summary>
/// プレイヤーHPUI
/// </summary>
/// <param name="enemy"></param>
void UiManager::PlayerHpDraw(int playerCount)
{
	DrawRotaGraph(515, 150, 0.7f, 0, uiHandle[FRAME], TRUE);

	DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);
	DrawRotaGraph(310, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);

	if (playerCount == 0)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(310, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	else if (playerCount == 1)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	else if (playerCount == 2)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
}