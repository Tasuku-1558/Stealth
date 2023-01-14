#pragma once

#include <string>

#include "DxLib.h"
#include "FirstStage.h"
#include "SecondStage.h"

class Enemy;
class HitChecker;

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

	void Draw(FirstStage::State state, Enemy* enemy, HitChecker* hitChecker);
	void Draw(SecondStage::State state, Enemy* enemy);

private:
	UiManager(const UiManager&);		//コピーコンストラクタ

	void StartGameDraw();				//ゲーム開始UI
	void PlayerHpDraw(Enemy* enemy);	//プレイヤーHPUI
	void OperationMethodDraw(HitChecker* hitChecker);	//操作方法説明UI


	//画像の種類
	enum Graphic
	{
		STAGE1,
		PLAYER_HP,			//プレイヤーHP画像
		PLAYER_HP_FRAME,	//プレイヤーHP枠画像
		OPERATION,			//操作方法説明画像
		BALLOON,			//吹き出し画像
		CLEAR,				//ゲームクリア画像
		STAGE2,
		FRAME,				//フレーム画像
		KEY,				//キー画像
		GRAPHIC_AMOUNT		//画像の数
	};

	int count;
	int uiHandle[GRAPHIC_AMOUNT];		//画像ハンドル


	//静的定数
	static const std::string FOLDER_PATH;			//画像格納フォルダ
	static const std::string UI_GRAPHIC_PATH;		//UI画像
	static const std::string FILENAME_EXTENSION;	//画像拡張子
};