#include "UiManager.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, alpha(255)
	, inc(-3)
	, MAX_ALPHA(255)
	, INC_SPEED(-1)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, UI_GRAPHIC_PATH("ui")
	, IMAGE_FILENAME_EXTENSION(".png")
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
UiManager::~UiManager()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void UiManager::Initialize()
{
	//Ui画像読み込み	
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		string uiPath = IMAGE_FOLDER_PATH + UI_GRAPHIC_PATH + to_string(i) + IMAGE_FILENAME_EXTENSION;
		uiHandle[i] = LoadGraph(uiPath.c_str());

		if (uiHandle[i] < 0)
		{
			printfDx("Ui画像読み込みに失敗[%d]\n", i);
		}
	}
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
/// 描画処理
/// </summary>
/// <param name="gameState">ゲームの状態</param>
/// <param name="playerCount">プレイヤーが見つかった回数</param>
/// <param name="hitUi"></param>
void UiManager::Draw(GameScene::GameState gameState, int playerCount, bool hitUi)
{
	switch (gameState)
	{
	case GameScene::GameState::START:
		break;

	case GameScene::GameState::GAME:
		StartGameDraw(STAGE1);
		PlayerHpDraw(playerCount);
		OperationMethodDraw(hitUi);

		//吹き出し画像描画
		DrawBillboard3D(VGet(0.0f, 0.0f, 800.0f), 0.5f, 0.5f, 200.0f, 0.0f, uiHandle[BALLOON], TRUE);
		break;

	case GameScene::GameState::GOAL:
		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
		break;
	}
}

/// <summary>
/// ゲーム開始UI
/// </summary>
/// <param name="graphic">Ui画像の種類</param>
void UiManager::StartGameDraw(Graphic graphic)
{
	if (alpha > MAX_ALPHA && inc > 0)
	{
		inc *= INC_SPEED;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawGraph(0, -100, uiHandle[graphic], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
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
	DrawRotaGraph(160, 80, 0.7f, 0, uiHandle[FRAME], TRUE);

	DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);

	//プレイヤーのHPが2の場合
	if (playerCount == 0)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	//プレイヤーのHPが1の場合
	else
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
}