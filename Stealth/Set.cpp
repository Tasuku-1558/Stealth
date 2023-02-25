#include "Set.h"


int Set::stageNo = 0;
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

void Set::SetStage(int stageNumber)
{
	stageNo = stageNumber;
}
