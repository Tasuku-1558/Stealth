#pragma once


class Set final
{
public:

	static Set& GetInstance();		//アドレスを返す

	void SetResult(bool result);
	void SetStage(int num);

	const int GetStage() { return number; }

	const bool GetResult() { return resultFlag; }

private:
	Set();
	Set(const Set&);		//コピーコンストラクタ
	virtual ~Set();

	int number;
	bool resultFlag;
};