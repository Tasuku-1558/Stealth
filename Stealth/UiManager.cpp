#include "UiManager.h"

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
	string path = FOLDER_PATH + UI_GRAPHIC_PATH; // フォルダパス + ファイル名
	string fullPath = path;

	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		fullPath = path + std::to_string(i) + FILENAME_EXTENSION;
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

void UiManager::Draw(PlayScene::State state)
{
	switch (state)
	{
	case PlayScene::START:
		
		break;

	case PlayScene::GAME:
		StartGameDraw();
		break;
	}
}

/// <summary>
/// ゲーム開始UI
/// </summary>
void UiManager::StartGameDraw()
{
	count += 1;

	if (count < 50)
	{
		DrawGraph(0, -50, uiHandle[STARGE1], TRUE);
	}
}