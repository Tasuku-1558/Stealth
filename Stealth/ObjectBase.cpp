#include "ObjectBase.h"


ObjectBase::ObjectBase()
	: position()
	, dir()
	, modelHandle(-1)
	, object()
{
	//ˆ—‚È‚µ
}

ObjectBase::~ObjectBase()
{
	//ˆ—‚È‚µ
}

/// <summary>
/// ƒQƒbƒ^[ŠÖ”ŒQ
/// </summary>
const VECTOR& ObjectBase::GetPosition() const
{
	return position;
}

const VECTOR& ObjectBase::GetDir() const
{
	return dir;
}

const int& ObjectBase::GetModelHandle() const
{
	return modelHandle;
}