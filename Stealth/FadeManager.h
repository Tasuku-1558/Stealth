#pragma once
#include "DxLib.h"

/// <summary>
/// ‰æ–ÊŒø‰ÊƒNƒ‰ƒX
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