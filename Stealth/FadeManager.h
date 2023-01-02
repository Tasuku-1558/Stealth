#pragma once
#include "DxLib.h"

/// <summary>
/// ‰æ–ÊŒø‰ÊƒNƒ‰ƒX
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