#pragma once
#include "DxLib.h"

/// <summary>
/// 画面効果クラス
/// </summary>
class FadeManager final
{
public:
	 FadeManager();
	 virtual ~FadeManager();

	void Activate();				//活性化処理
	void FadeMove();				//画面効果処理
	void Draw();					//描画処理

private:

	int fade;
	int fadeInc;

	//静的定数
	static const int BLACK;			//フェードのカラー
};