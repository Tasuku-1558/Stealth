#include "ObjectBase.h"


ObjectBase::ObjectBase()
	: position()
	, dir()
	, modelHandle(-1)
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
/// <returns></returns>
const VECTOR& ObjectBase::GetPosition() const
{
	return position;
}

const VECTOR& ObjectBase::GetDir() const
{
	return dir;
}