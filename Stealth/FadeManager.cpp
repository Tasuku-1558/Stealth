#include "FadeManager.h"
#include "PreCompiledHeader.h"
#include <math.h>


/// <summary>
/// コンストラクタ
/// </summary>
FadeManager::FadeManager()
	: fade(0)
	, fadeInc(2)
	, fadeEnd(false)
	, TOP_LEFT_VERTEX_X(0)
	, TOP_LEFT_VERTEX_Y(0)
	, BLACK(GetColor(0, 0, 0))
	, MAX_FADE(255)
	, FADE_SPEED(-1)
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
		fadeInc *= FADE_SPEED;
		fadeEnd = true;
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
	DrawBox(TOP_LEFT_VERTEX_X, TOP_LEFT_VERTEX_Y, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, fade);
}