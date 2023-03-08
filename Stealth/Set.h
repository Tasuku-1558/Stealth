#pragma once


class Set final
{
public:

	static Set& GetInstance();		//アドレスを返す

	static void SetResult(bool result);
	static bool GetResult() { return resultFlag; }

private:
	Set();
	Set(const Set&);		//コピーコンストラクタ
	virtual ~Set();

	static bool resultFlag;
};