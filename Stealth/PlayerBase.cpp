#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 500.0f;						//移動速度
const int	 PlayerBase::HP		  = 50;							//プレイヤーのHP
const VECTOR PlayerBase::POSITION = { 3800.0f, 0.0f, -540.0f };		//モデルの位置
const VECTOR PlayerBase::DIR	  = { -1.0f,0.0f,0.0f };			//モデルの向き
const VECTOR PlayerBase::UP		  = { -1,  0,  0};				//上方向
const VECTOR PlayerBase::DOWN	  = { 1,  0, 0};				//下方向
const VECTOR PlayerBase::LEFT	  = {0,  0,  -1};				//左方向
const VECTOR PlayerBase::RIGHT	  = { 0,  0,  1};				//右方向


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