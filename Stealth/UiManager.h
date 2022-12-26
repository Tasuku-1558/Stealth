#pragma once

#include "DxLib.h"
#include "PlayScene.h"
#include <string>		//文字列型クラス


/// <summary>
/// UI管理クラス
/// </summary>
class UiManager final
{
public:
	 UiManager();
	~UiManager();

	void Initialize();
	void Finalize();

	void Draw(PlayScene::State state);


private:
	UiManager(const UiManager&);		//コピーコンストラクタ

	void StartGameDraw();				//ゲーム開始UI


	//画像の種類
	enum Graphic
	{
		STARGE1,
		GRAPHIC_AMOUNT
	};

	int count;
	int uiHandle[GRAPHIC_AMOUNT];		//画像ハンドル


	//静的定数
	static const std::string FOLDER_PATH;			//画像格納フォルダ
	static const std::string UI_GRAPHIC_PATH;		//UI画像
	static const std::string FILENAME_EXTENSION;	//画像拡張子
};