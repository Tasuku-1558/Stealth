#pragma once


class Set final
{
public:

	Set();
	virtual ~Set();

	static Set& GetInstance();		//�A�h���X��Ԃ�

	void SetResult(bool result);
	bool GetResult() { return resultFlag; }

private:
	Set(const Set&);		//�R�s�[�R���X�g���N�^

	bool resultFlag;
};