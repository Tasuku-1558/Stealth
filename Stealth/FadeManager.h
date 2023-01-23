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


	void FadeMove();				//‰æ–ÊŒø‰Êˆ—
	void Draw();					//•`‰æˆ—

	int Fade() { return fade; }

private:

	int fade;
	int fadeInc;
};