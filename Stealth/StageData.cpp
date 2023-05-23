#include "StageData.h"


StageData::StageData()
	: stageHandle()
	, s()
	, characterPack(0)
	, rawNum(0)
	, columnNum(0)
	, num(0)
	, buffer()
	, endFlag(false)
{
	FILE* filePointer = nullptr;								//ファイルのポインタを宣言
	fopen_s(&filePointer, "Data/Csv/Stage1.csv", "r");			//fopen_s関数でcsvを読み取り形式で開く

	if (filePointer == NULL)									//filePointerが空の場合は
	{
		DebugBreak();											//デバッグ中止
	}

	memset(buffer, 0, sizeof(buffer));							//memset関数でメモリにbufferをセットし、sizeof演算子で要素数を決める

	while (1)
	{
		while (1)
		{
			characterPack = fgetc(filePointer);										//fgetc関数でfilepointerから文字を読んでcharacterPackに格納
			if (characterPack == EOF)
			{
				endFlag = true;														//EndOfFileを検出して
				break;																//ループを抜ける
			}
			if (characterPack != ',' && characterPack != '\n')						//区切りか改行でなければ
			{
				strcat_s(buffer, (const char*)&characterPack);						//strcat_s関数でbufferに連結し、const char関数で書き換える
			}
			else
			{
				num = atoi(buffer);													//atoi関数でbufferをint型に直して、ローカル変数numに代入
				s[columnNum][rawNum] = stageHandle[num];			//num番目のチップ画像のハンドルを取得
				memset(buffer, 0, sizeof(buffer));									//bufferをリセット
				break;																//区切りか改行なのでループを抜ける
			}
		}
		if (endFlag)																//1マップ分になったら
		{
			break;																	//ループを抜ける
		}
		if (characterPack == ',')													//区切りを検出したら
		{
			columnNum++;															//列の数を増やす
		}
		if (characterPack == '\n')													//改行だったら
		{
			rawNum++;																//行を増やす
			columnNum = 0;															//列を0にする
		}
	}

	fclose(filePointer);															//ファイルを閉じる
}

StageData::~StageData()
{
	//処理なし
}