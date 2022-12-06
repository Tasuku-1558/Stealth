#include "ObjectBase.h"


ObjectBase::ObjectBase()
	: position()
	, dir()
	, modelHandle(-1)
{
	//ˆ—‚È‚µ
}

ObjectBase::~ObjectBase()
{
	//ˆ—‚È‚µ
}

//ƒQƒbƒ^[ŠÖ”ŒQ
const VECTOR& ObjectBase::GetPosition() const
{
	return position;
}

const VECTOR& ObjectBase::GetDir() const
{
	return dir;
}