#include "UiManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, stageCount(0)
	, alpha(0)
	, inc(0)
	, IMAGE_FOLDER_PATH("data/image/")
	, UI_GRAPHIC_PATH("ui")
	, IMAGE_FILENAME_EXTENSION(".png")
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
	string failePath;
	string fullPath = failePath = IMAGE_FOLDER_PATH + UI_GRAPHIC_PATH;		//フォルダパス + ファイル名
	
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		fullPath = failePath + std::to_string(i) + IMAGE_FILENAME_EXTENSION;
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
	stageCount = 0;
	alpha = 255;
	inc = -3;
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
/// FirstStageのUI描画処理
/// </summary>
/// <param name="state"></param>
/// <param name="playerCount"></param>
/// <param name="hitUi"></param>
void UiManager::Draw(FirstStage::State state, int playerCount, bool hitUi)
{
	switch (state)
	{
	case FirstStage::State::START:
		
		break;

	case FirstStage::State::GAME:

		StartGameDraw(STAGE1);
		PlayerHpDraw(playerCount);
		OperationMethodDraw(hitUi);

		//吹き出し画像描画
		DrawBillboard3D(VGet(-800.0f, 0.0f, 0.0f), 0.5f, 0.5f, 200.0f, 0.0f, uiHandle[BALLOON], TRUE);
		break;

	case FirstStage::State::GOAL:
		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
		break;
	}
}

/// <summary>
/// SecondStageのUI描画処理
/// </summary>
/// <param name="state"></param>
/// <param name="playerCount"></param>
//void UiManager::Draw(SecondStage::State state, int playerCount)
//{
//	switch (state)
//	{
//	case SecondStage::State::START:
//		
//		break;
//
//	case SecondStage::State::GAME:
//		
//		StartGameDraw(STAGE2);
//		PlayerHpDraw(playerCount);
//		break;
//
//	case SecondStage::State::GOAL:
//		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
//		break;
//	}
//}
//
///// <summary>
///// ThirdStageのUI描画処理
///// </summary>
///// <param name="state"></param>
///// <param name="playerCount"></param>
//void UiManager::Draw(ThirdStage::State state, int playerCount)
//{
//	switch (state)
//	{
//	case ThirdStage::State::START:
//
//		break;
//
//	case ThirdStage::State::GAME:
//
//		StartGameDraw(STAGE3);
//		PlayerHpDraw(playerCount);
//		break;
//
//	case ThirdStage::State::GOAL:
//		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
//		break;
//	}
//}
//
///// <summary>
///// FourthStageのUI描画処理
///// </summary>
///// <param name="state"></param>
///// <param name="playerCount"></param>
//void UiManager::Draw(FourthStage::State state, int playerCount)
//{
//	switch (state)
//	{
//	case FourthStage::State::START:
//
//		break;
//
//	case FourthStage::State::GAME:
//
//		StartGameDraw(STAGE4);
//		PlayerHpDraw(playerCount);
//		break;
//
//	case FourthStage::State::GOAL:
//		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
//		break;
//	}
//}
//
///// <summary>
///// FifthStageのUI描画処理
///// </summary>
///// <param name="state"></param>
///// <param name="playerCount"></param>
//void UiManager::Draw(FifthStage::State state, int playerCount)
//{
//	switch (state)
//	{
//	case FifthStage::State::START:
//
//		break;
//
//	case FifthStage::State::GAME:
//
//		StartGameDraw(STAGE5);
//		PlayerHpDraw(playerCount);
//		break;
//
//	case FifthStage::State::GOAL:
//		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
//		break;
//	}
//}

/// <summary>
/// ゲーム開始UI
/// </summary>
/// <param name="graphic"></param>
void UiManager::StartGameDraw(Graphic graphic)
{
	stageCount++;

	if (stageCount < 190)
	{
		if (alpha > 255 && inc > 0)
		{
			inc *= -1;
		}

		alpha += inc;
	}

	if (stageCount < 200)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		DrawGraph(0, -100, uiHandle[graphic], TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
	}
}

/// <summary>
/// 操作方法説明UI
/// </summary>
/// <param name="hitUi"></param>
void UiManager::OperationMethodDraw(bool hitUi)
{
	//吹き出し画像に当たっているなら
	if (hitUi)
	{
		DrawGraph(0, 20, uiHandle[OPERATION], TRUE);
	}
}

/// <summary>
/// ケーキを持っているかのUI
/// </summary>
/// <param name="cakeGet"></param>
void UiManager::CakeGetDraw(bool cakeGet)
{
	//ケーキを持っているなら
	if (cakeGet)
	{
		DrawRotaGraph(110, 220, 0.05f, 0, uiHandle[CAKE], TRUE);
	}
}

/// <summary>
/// プレイヤーHPUI
/// </summary>
/// <param name="playerCount"></param>
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