#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

 ///<summary>
 ///ステージCSV読み込みクラス
 ///</summary>
class StageData final
{
public:
	StageData(const char* csvName);
	virtual ~StageData();


	vector<string> strvec;
	int num[128];
	
private:
	StageData(const StageData&);	//コピーコンストラクタ

	vector<string> Split(string& input, char delimiter);

};