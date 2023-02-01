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

	void Activate();				//Šˆ«‰»ˆ—
	void FadeMove();				//‰æ–ÊŒø‰Êˆ—
	void Draw();					//•`‰æˆ—

private:

	int fade;
	int fadeInc;
};