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


	void FadeMove();				//��ʌ��ʏ���
	void Draw();					//�`�揈��

	int Fade() { return fade; }

private:

	int fade;
	int fadeInc;
};