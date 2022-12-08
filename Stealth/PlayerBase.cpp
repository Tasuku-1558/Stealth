#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//移動速度
const VECTOR PlayerBase::POSITION = { 0.0f, 0.0f, 0.0f };		//モデルの位置
const VECTOR PlayerBase::DIR	  = { 0.0f,0.0f,1.0f };			//モデルの向き
const int	 PlayerBase::HP		  = 2;							//プレイヤーのHP

PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
	, hp(0)
{
	//処理なし
}

PlayerBase::~PlayerBase()
{
	//処理なし
}