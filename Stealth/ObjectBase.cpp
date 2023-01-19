#include "ObjectBase.h"


ObjectBase::ObjectBase()
	: position()
	, dir()
	, modelHandle(-1)
	, object()
{
	//�����Ȃ�
}

ObjectBase::~ObjectBase()
{
	//�����Ȃ�
}

/// <summary>
/// �Q�b�^�[�֐��Q
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