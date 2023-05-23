#pragma once
#include "PreCompiledHeader.h"

class StageData final
{
public:
	StageData();
	virtual ~StageData();

	int s[BLOCK_NUM_X][BLOCK_NUM_Z];


private:
	StageData(const StageData&);		//コピーコンストラクタ

	int stageHandle[256];

	int characterPack;				//文字を格納する変数
	int rawNum;					//横方向のタイルナンバー
	int columnNum;				//縦方向のタイルナンバー
	int num;						//タイルの番号
	char buffer[10];				//文字列変数
	bool eofFlag;			//eof（end of file）検出フラグ

};