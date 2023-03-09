#include "PlayerBase.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerBase::PlayerBase()
	: inputDirection()
	, nextPosition()
	, playerFindCount(0)
	, playerFindImage(0)
	, findImageX(50)
	, findImageY(-100)
	, speed(0.0f)
	, initialTime(0.8f)
	, inputFlag(false)
	, findImageFlag(false)
	, spottedSeFlag(false)
	, SPEED(450.0f)
	, OPACITY(0.05f)
	, RADIUS(100.0f)
	, POSITION({ 0.0f, 0.0f, 0.0f })
	, DIRECTION({ 0.0f,0.0f,1.0f })
	, UP({ 0.0f, 0.0f, 1.0f })
	, DOWN({ 0.0f, 0.0f, -1.0f })
	, LEFT({ -1.0f, 0.0f, 0.0f })
	, RIGHT({ 1.0f, 0.0f, 0.0f })
	, AFTER_IMAGE_ADJUSTMENT({ 0.0f,10.0f,0.0f })
	, AFTER_IMAGE_COLOR(GetColorF(0.0f, 0.0f, 1.0f, 1.0f))
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBase::~PlayerBase()
{
	//�����Ȃ�
}