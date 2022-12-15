#include "EnemyBase.h"


const float  EnemyBase::SPEED	 = 450.0f;						//移動速度
const VECTOR EnemyBase::POSITION = { -2700.0f, 100.0f, 1300.0f };	//モデルの位置
const VECTOR EnemyBase::DIR		 = { 0.0f,0.0f,-1.0f };			//モデルの向き

EnemyBase::EnemyBase()
{
	//処理なし
}

EnemyBase::~EnemyBase()
{
	//処理なし
}