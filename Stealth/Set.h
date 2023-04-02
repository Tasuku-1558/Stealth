#pragma once


class Set final
{
public:

	static Set& GetInstance();		//アドレスを返す

	void SetResult(bool result);

	const bool GetResult() { return resultFlag; }

private:
	Set();
	Set(const Set&);		//コピーコンストラクタ
	virtual ~Set();

	bool resultFlag;
};