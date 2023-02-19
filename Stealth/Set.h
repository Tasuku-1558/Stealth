#pragma once


class Set final
{
public:

	Set();
	virtual ~Set();

	static Set& GetInstance();		//アドレスを返す

	void SetResult(bool result);
	bool GetResult() { return resultFlag; }

private:
	Set(const Set&);		//コピーコンストラクタ

	bool resultFlag;
};