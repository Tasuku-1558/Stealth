#include "StageData.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="csvName">CSVファイルの名前</param>
StageData::StageData(const char* csvName)
	: stageNum()
{
	ifstream ifs(csvName);

	string line;

	//読み込み失敗ならエラー
	if (!ifs)
	{
		printfDx("CSVファイルの読み込みに失敗[%s]\n", csvName);
	}

	//CSVファイルの最後の行まで回す
	while (getline(ifs, line))
	{
		strvec = Split(line, ',');

		for (int i = 0; i < strvec.size(); i++)
		{
			//整数型へ変換
			stageNum[i] = stoi(strvec.at(i));
		}
	}
}

/// <summary>
/// デストラクタ
/// </summary>
StageData::~StageData()
{
	//処理なし
}

/// <summary>
/// CSVファイルの値の読み込み
/// </summary>
/// <param name="input">string変数格納</param>
/// <param name="delimiter">カンマ文字格納</param>
/// <returns>読み込んだ値を返す</returns>
vector<string> StageData::Split(string& input, char delimiter)
{
	istringstream stream(input);
	string field;
	vector<string> result;

	while (getline(stream, field, delimiter))
	{
		result.emplace_back(field);
	}

	return result;
}