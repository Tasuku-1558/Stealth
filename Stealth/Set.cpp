#include "Set.h"


Set::Set()
	: resultFlag(false)
{
	//ˆ—‚È‚µ
}

Set::~Set()
{
	//ˆ—‚È‚µ
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