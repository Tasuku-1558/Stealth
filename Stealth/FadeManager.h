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


	void FadeMove();				//画面効果処理
	void Draw();					//描画処理

	int Fade() { return fade; }

private:

	int fade;
	int fadeInc;
};