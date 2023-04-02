#include "PlayerBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
PlayerBase::PlayerBase()
	: playerFindCount(0)
	, playerFindImage(0)
	, speed(0.0f)
	, inputFlag(false)
	, findImageFlag(false)
	, spottedSeFlag(false)
	, inputDirection()
	, nextPosition()
	, FIND_IMAGE_X(50)
	, FIND_IMAGE_Y(-100)
	, SPEED(450.0f)
	, OPACITY(0.05f)
	, RADIUS(100.0f)
	, INITIAL_TIME(0.8f)
	, POSITION({ 0.0f, 0.0f, 0.0f })
	, DIRECTION({ 0.0f,0.0f,1.0f })
	, UP({ 0.0f, 0.0f, 1.0f })
	, DOWN({ 0.0f, 0.0f, -1.0f })
	, LEFT({ -1.0f, 0.0f, 0.0f })
	, RIGHT({ 1.0f, 0.0f, 0.0f })
	, AFTER_IMAGE_ADJUSTMENT({ 0.0f,10.0f,0.0f })
	, AFTER_IMAGE_COLOR(GetColorF(0.0f, 0.0f, 1.0f, 1.0f))
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBase::~PlayerBase()
{
	//処理なし
}