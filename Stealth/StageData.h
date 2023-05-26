#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "PreCompiledHeader.h"

using namespace std;

 ///<summary>
 ///ステージCSV読み込みクラス
 ///</summary>
class StageData final
{
public:
	StageData(const char* csvName);
	virtual ~StageData();

	int Get() { return num; }

private:
	StageData(const StageData&);	//コピーコンストラクタ

	vector<string> Split(string& input, char delimiter);

	int num;
	vector<string> strvec;

};