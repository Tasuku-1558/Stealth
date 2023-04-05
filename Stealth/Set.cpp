#include "Set.h"


Set::Set()
	: resultFlag(false)
	, number(0)
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

void Set::SetStage(int num)
{
	number = num;
}