#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//移動速度
const VECTOR PlayerBase::POSITION = VGet(0.0f, 200.0f, 150.0f);	//モデルの位置

PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
{
	//処理なし
}

PlayerBase::~PlayerBase()
{
	//処理なし
}