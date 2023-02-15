#include "Set.h"


Set::Set()
	: resultFlag(0)
{
}

Set::~Set()
{
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