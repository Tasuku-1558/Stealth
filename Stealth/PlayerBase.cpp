#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//ˆÚ“®‘¬“x
const VECTOR PlayerBase::POSITION = VGet(0.0f, 200.0f, 150.0f);	//ƒ‚ƒfƒ‹‚ÌˆÊ’u

PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
{
	//ˆ—‚È‚µ
}

PlayerBase::~PlayerBase()
{
	//ˆ—‚È‚µ
}