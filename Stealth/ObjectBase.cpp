#include "ObjectBase.h"


ObjectBase::ObjectBase()
	: position()
	, dir()
	, modelHandle(-1)
{
	//処理なし
}

ObjectBase::~ObjectBase()
{
	//処理なし
}

//ゲッター関数群
const VECTOR& ObjectBase::GetPosition() const
{
	return position;
}

const VECTOR& ObjectBase::GetDir() const
{
	return dir;
}