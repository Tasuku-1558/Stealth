#include "EnemyBase.h"


const float  EnemyBase::SPEED	 = 450.0f;						//移動速度
const VECTOR EnemyBase::POSITION = { 500.0f, 0.0f, 400.0f };	//モデルの位置
const VECTOR EnemyBase::DIR		 = { 0.0f,0.0f,-1.0f };			//モデルの向き

EnemyBase::EnemyBase()
{
	//処理なし
}

EnemyBase::~EnemyBase()
{
	//処理なし
}