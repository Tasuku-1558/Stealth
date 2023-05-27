#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

 ///<summary>
 ///�X�e�[�WCSV�ǂݍ��݃N���X
 ///</summary>
class StageData final
{
public:
	StageData(const char* csvName);
	virtual ~StageData();


	vector<string> strvec;
	int num[128];
	
private:
	StageData(const StageData&);	//�R�s�[�R���X�g���N�^

	vector<string> Split(string& input, char delimiter);

};