#include "Set.h"


Set::Set()
	: resultFlag(false)
	, stageNumber(0)
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

void Set::SetStage(int number)
{
	stageNumber = number;
}