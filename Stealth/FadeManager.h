#pragma once
#include "DxLib.h"

/// <summary>
/// ��ʌ��ʃN���X
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