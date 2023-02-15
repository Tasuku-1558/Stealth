#pragma once

#include <string>

#include "DxLib.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "FourthStage.h"
#include "FifthStage.h"


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

	void Draw(FirstStage::State state,
			  int playerCount, bool hitUi);	//FirstStageのUI描画処理

	void Draw(SecondStage::State state, 
			  int playerCount);				//SecondStageのUI描画処理

	void Draw(ThirdStage::State state,
			  int playerCount);				//ThirdStageの描画処理

	void Draw(FourthStage::State state,
			  int playerCount);				//FourthStageの描画処理

	void Draw(FifthStage::State state,
		int playerCount);					//FifthStageの描画処理

	void CakeGetDraw(bool cakeGet);			//ケーキを持っているかのUI

private:
	UiManager(const UiManager&);			//コピーコンストラクタ

	//画像の種類
	enum Graphic
	{
		STAGE1,				//ステージ1スタート画像
		PLAYER_HP,			//プレイヤーHP画像
		PLAYER_HP_FRAME,	//プレイヤーHP枠画像
		OPERATION,			//操作方法説明画像
		BALLOON,			//吹き出し画像
		CLEAR,				//ゲームクリア画像
		STAGE2,				//ステージ2スタート画像
		FRAME,				//プレイヤーHPフレーム画像
		CAKE,				//ケーキ画像
		STAGE3,				//ステージ3スタート画像
		STAGE4,				//ステージ4スタート画像
		STAGE5,				//ステージ5スタート画像
		GRAPHIC_AMOUNT		//画像の数
	};

	void StartGameDraw(UiManager::Graphic graphic);	//ゲーム開始UI
	void PlayerHpDraw(int playerCount);				//プレイヤーHPUI
	void OperationMethodDraw(bool hitUi);			//操作方法説明UI

	int stageCount;									//ステージ名称表示カウント
	
	int uiHandle[GRAPHIC_AMOUNT];					//画像ハンドル


	//静的定数
	static const std::string IMAGE_FOLDER_PATH;		//画像格納フォルダ
	static const std::string UI_GRAPHIC_PATH;		//UI画像
	static const std::string FILENAME_EXTENSION;	//画像拡張子
};