#include "FadeManager.h"
#include "PreCompiledHeader.h"
#include <math.h>


/// <summary>
/// コンストラクタ
/// </summary>
FadeManager::FadeManager()
	: fade(0)
	, fadeInc(2)
	, BLACK(GetColor(0, 0, 0))
	, MAX_FADE(255)
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
/// 画面効果処理
/// </summary>
void FadeManager::FadeMove()
{
	//画面効果の増分チェック
	if (fade > MAX_FADE && fadeInc > 0)
	{
		fadeInc *= -1;
	}

	fade += fadeInc;
}

/// <summary>
/// 描画処理
/// </summary>
void FadeManager::Draw()
{
	//画面全体フェード用の矩形黒色の背景を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, fade);
}