#include "FadeManager.h"
#include "PreCompiledHeader.h"
#include <math.h>


FadeManager::FadeManager()
	: fade(0)
	, fadeInc(2)
{
	//�����Ȃ�
}

FadeManager::~FadeManager()
{
	//�����Ȃ�
}

void FadeManager::FadeMove()
{
	//��ʌ��ʂ̑����`�F�b�N
	if (fade > 255 && fadeInc > 0)
	{
		fadeInc *= -1;
	}

	if (fade < 0 && fadeInc < 0)
	{
		fadeInc *= -1;
	}

	fade += fadeInc;
}

void FadeManager::Draw()
{
	//��ʑS�̃t�F�[�h�p�̋�`�������`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xffffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, fade);
}