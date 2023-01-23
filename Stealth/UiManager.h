#pragma once

#include <string>

#include "DxLib.h"
#include "FirstStage.h"
#include "SecondStage.h"


/// <summary>
/// UI管理クラス
/// </summary>
class UiManager final
{
public:
	 UiManager();
	 virtual ~UiManager();

	void Initialize();		//初期化処理
	void Activate();		//活性化処理
	void Finalize();		//終了処理

	void Draw(FirstStage::State state, int playerCount, bool hitUi);	//FirstStage描画処理
	void Draw(SecondStage::State state, int playerCount);				//SecondStage描画処理

	
private:
	UiManager(const UiManager&);			//コピーコンストラクタ

	void StartGameDraw();					//ゲーム開始UI
	void PlayerHpDraw(int playerCount);		//プレイヤーHPUI
	void OperationMethodDraw(bool hitUi);	//操作方法説明UI


	//画像の種類
	enum Graphic
	{
		STAGE1,				//ステージ１スタート画像
		PLAYER_HP,			//プレイヤーHP画像
		PLAYER_HP_FRAME,	//プレイヤーHP枠画像
		OPERATION,			//操作方法説明画像
		BALLOON,			//吹き出し画像
		CLEAR,				//ゲームクリア画像
		STAGE2,				//ステージ２スタート画像
		FRAME,				//フレーム画像
		KEY,				//プレイヤー移動キー画像
		GRAPHIC_AMOUNT		//画像の数
	};

	int count;
	
	int uiHandle[GRAPHIC_AMOUNT];					//画像ハンドル
	

	//静的定数
	static const std::string IMAGE_FOLDER_PATH;		//画像格納フォルダ
	static const std::string UI_GRAPHIC_PATH;		//UI画像
	static const std::string FILENAME_EXTENSION;	//画像拡張子
};