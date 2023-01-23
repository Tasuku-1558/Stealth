#include "ObjectBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
ObjectBase::ObjectBase()
	: position()
	, dir()
	, modelHandle(-1)
	, object()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectBase::~ObjectBase()
{
	//処理なし
}

/// <summary>
/// ゲッター関数群
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