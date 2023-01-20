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


	void FadeMove();
	void Draw();

	int Fade() { return fade; }

private:

	int fade;
	int fadeInc;
};