#pragma once


class Set final
{
public:

	static Set& GetInstance();		//�A�h���X��Ԃ�

	void SetResult(bool result);
	void SetStage(int num);

	const int GetStage() { return number; }

	const bool GetResult() { return resultFlag; }

private:
	Set();
	Set(const Set&);		//�R�s�[�R���X�g���N�^
	virtual ~Set();

	int number;
	bool resultFlag;
};