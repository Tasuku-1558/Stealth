#pragma once
#include "DxLib.h"

/// <summary>
/// 画面効果クラス
/// </summary>
class FadeManager final
{
public:
	 FadeManager();
	~FadeManager();


	void FadeMove();
	void Draw();

private:

	int fade;
	int fadeInc;
};