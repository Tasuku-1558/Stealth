#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "PreCompiledHeader.h"

using namespace std;

 ///<summary>
 ///�X�e�[�WCSV�ǂݍ��݃N���X
 ///</summary>
class StageData final
{
public:
	StageData(const char* csvName);
	virtual ~StageData();

	int Get() { return num; }

private:
	StageData(const StageData&);	//�R�s�[�R���X�g���N�^

	vector<string> Split(string& input, char delimiter);

	int num;
	vector<string> strvec;

};