#pragma once

#include <string>
#include "GameScene.h"

using namespace std;

/// <summary>
/// UI管理クラス
/// </summary>
class UiManager final
{
public:
	UiManager();
	virtual ~UiManager();

	void Draw(GameScene::GameState gameState,
			  int playerCount, bool hitUi);	//描画処理

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
		GRAPHIC_AMOUNT,		//画像の数
	};

	void Initialize();								//初期化処理
	void Finalize();								//終了処理
	void StartGameDraw(UiManager::Graphic graphic);	//ゲーム開始UI
	void PlayerHpDraw(int playerCount);				//プレイヤーHPUI
	void OperationMethodDraw(bool hitUi);			//操作方法説明UI

	int uiHandle[GRAPHIC_AMOUNT];					//画像ハンドル格納用
	int alpha;										//透過度
	int inc;

	//定数
	const int	 MAX_ALPHA;					//最大透過度
	const string IMAGE_FOLDER_PATH;			//画像格納フォルダ
	const string UI_GRAPHIC_PATH;			//UI画像
	const string IMAGE_FILENAME_EXTENSION;	//画像拡張子
};