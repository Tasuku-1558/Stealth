#include "PlayerBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
PlayerBase::PlayerBase()
	: playerFindCount(0)
	, playerFindImage(0)
	, afterImageModel()
	, speed(0.0f)
	, initialTime(0.0f)
	, inputFlag(false)
	, findImageFlag(false)
	, spottedSeFlag(false)
	, inputDirection()
	, nextPosition()
	, pastPosition()
	, FIND_IMAGE_X(50)
	, FIND_IMAGE_Y(-100)
	, AFTER_IMAGE_NUMBER(12)
	, KEY_INPUT_PATTERN(4)
	, MATERIAL_INDEX(0)
	, INITIAL_SPEED(450.0f)
	, OPACITY(0.05f)
	, RADIUS(100.0f)
	, Y_ANGLE(0.0f)
	, MAX_INITIAL_TIME(0.8f)
	, INITIAL_TIME(0.0f)
	, STOP_SPEED(0.0f)
	, MAX_INPUT_DIRECTION(1.0f)
	, INITIAL_POSITION({ 0.0f, 0.0f, 0.0f })
	, INITIAL_DIRECTION({ 0.0f,0.0f,1.0f })
	, UP({ 0.0f, 0.0f, 1.0f })
	, DOWN({ 0.0f, 0.0f, -1.0f })
	, LEFT({ -1.0f, 0.0f, 0.0f })
	, RIGHT({ 1.0f, 0.0f, 0.0f })
	, AFTER_IMAGE_ADJUSTMENT({ 0.0f,10.0f,0.0f })
	, IMAGE_FOLDER_PATH("Data/Image/")
	, PLAYER_FIND_PATH("playerFind.png")
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