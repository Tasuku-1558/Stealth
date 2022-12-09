#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 500.0f;						//移動速度
const int	 PlayerBase::HP		  = 2;							//プレイヤーのHP
const VECTOR PlayerBase::POSITION = { 0.0f, 0.0f, 0.0f };		//モデルの位置
const VECTOR PlayerBase::DIR	  = { 0.0f,0.0f,1.0f };			//モデルの向き
const VECTOR PlayerBase::UP		  = {  0,0, 1 };				//上方向
const VECTOR PlayerBase::DOWN	  = {  0,0,-1 };				//下方向
const VECTOR PlayerBase::LEFT	  = { -1,0, 0 };				//左方向
const VECTOR PlayerBase::RIGHT	  = {  1,0, 0 };				//右方向


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