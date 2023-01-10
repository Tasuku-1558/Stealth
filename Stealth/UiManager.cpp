#include "UiManager.h"
#include "Enemy.h"
#include "HitChecker.h"

using std::string;

const string UiManager::FOLDER_PATH		   = "data/image/";		//画像ファイルのパス
const string UiManager::UI_GRAPHIC_PATH    = "ui";				//UI画像
const string UiManager::FILENAME_EXTENSION = ".png";			//画像拡張子


UiManager::UiManager()
	: uiHandle()
	, count(0)
{
	//処理なし
}

UiManager::~UiManager()
{
	//終了処理が呼ばれてなければ
	if (uiHandle[0] != NULL)
	{
		Finalize();
	}
}

void UiManager::Initialize()
{
	//UI画像読み込み
	string failePath = FOLDER_PATH + UI_GRAPHIC_PATH; // フォルダパス + ファイル名
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

void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}
}

void UiManager::Draw(PlayScene::State state, Enemy* enemy, HitChecker* hitChecker)
{
	//吹き出し画像描画
	DrawBillboard3D(VGet(-800.0f, 0.0f, 0.0f), 0.5f, 0.5f, 200.0f, 0.0f, uiHandle[BALLOON], TRUE);

	switch (state)
	{
	case PlayScene::START:
		
		break;

	case PlayScene::GAME:
		StartGameDraw();
		PlayerHpDraw(enemy);
		OperationMethodDraw(hitChecker);
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
		DrawGraph(0, -50, uiHandle[STARGE1], TRUE);
	}
}

/// <summary>
/// 操作方法説明UI
/// </summary>
/// <param name="hitChecker"></param>
void UiManager::OperationMethodDraw(HitChecker* hitChecker)
{
	if (hitChecker->UI())
	{
		DrawGraph(0, 20, uiHandle[OPERATION], TRUE);
	}
}

/// <summary>
/// プレイヤーHPUI
/// </summary>
/// <param name="enemy"></param>
void UiManager::PlayerHpDraw(Enemy* enemy)
{
	DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);
	DrawRotaGraph(310, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);

	if (enemy->GetPlayerCount() == 0)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(310, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	else if (enemy->GetPlayerCount() == 1)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	else if (enemy->GetPlayerCount() == 2)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
}