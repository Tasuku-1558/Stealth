#pragma once


class Set final
{
public:

	static Set& GetInstance();		//アドレスを返す

	static void SetResult(bool result);
	static bool GetResult() { return resultFlag; }

	static void SetStage(int stageNumber);
	static bool GetStage() { return stageNo; }


private:
	Set();
	Set(const Set&);		//コピーコンストラクタ
	virtual ~Set();

	static bool resultFlag;
	static int stageNo;
};