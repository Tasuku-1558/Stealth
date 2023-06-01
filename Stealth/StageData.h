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

	int num[256];			//CSVファイルの値格納用
	
private:
	StageData(const StageData&);	//コピーコンストラクタ

	vector<string> Split(string& input, char delimiter);	//CSVファイルの値の読み込み

	vector<string> strvec;
};