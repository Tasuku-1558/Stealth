#include "Set.h"


bool Set::resultFlag = false;

Set::Set()
{
	//�����Ȃ�
}

Set::~Set()
{
	//�����Ȃ�
}

Set& Set::GetInstance()
{
	static Set set;
	return set;
}

void Set::SetResult(bool result)
{
	resultFlag = result;
}