#include "FadeManager.h"
#include "PreCompiledHeader.h"
#include <math.h>


/// <summary>
/// コンストラクタ
/// </summary>
FadeManager::FadeManager()
	: fade(0)
	, fadeInc(2)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
FadeManager::~FadeManager()
{
	//処理なし
}

/// <summary>
/// 活性化処理
/// </summary>
void FadeManager::Activate()
{
	fade = 0;
	fadeInc = 2;
}

/// <summary>
/// 画面効果処理
/// </summary>
void FadeManager::FadeMove()
{
	//画面効果の増分チェック
	if (fade > 255 && fadeInc > 0)
	{
		fadeInc *= -1;
	}

	/*if (fade < 0 && fadeInc < 0)
	{
		fadeInc *= -1;
	}*/

	fade += fadeInc;
}

/// <summary>
/// 描画処理
/// </summary>
void FadeManager::Draw()
{
	//画面全体フェード用の矩形半透明描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xffffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, fade);
}