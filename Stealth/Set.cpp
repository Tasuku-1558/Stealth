#include "Set.h"


bool Set::resultFlag = false;

Set::Set()
{
	//処理なし
}

Set::~Set()
{
	//処理なし
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