#pragma once


class Set final
{
public:

	static Set& GetInstance();		//�A�h���X��Ԃ�

	static void SetResult(bool result);
	static bool GetResult() { return resultFlag; }

private:
	Set();
	Set(const Set&);		//�R�s�[�R���X�g���N�^
	virtual ~Set();

	static bool resultFlag;
};