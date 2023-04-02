#include "Set.h"


Set::Set()
	: resultFlag(false)
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