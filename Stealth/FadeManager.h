#pragma once
#include "DxLib.h"

/// <summary>
/// ��ʌ��ʃN���X
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