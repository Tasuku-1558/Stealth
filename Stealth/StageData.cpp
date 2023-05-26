#include "StageData.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="csvName">CSV�t�@�C���̖��O</param>
StageData::StageData(const char* csvName)
	: num(0)
{
	ifstream ifs(csvName);

	string line;

	while (getline(ifs, line))
	{
		strvec = Split(line, ',');

		for (int i = 0; i < strvec.size(); i++)
		{
			num = stoi(strvec.at(i));
		}
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageData::~StageData()
{
	//�����Ȃ�
}

vector<string> StageData::Split(string& input, char delimiter)
{
	istringstream stream(input);
	string field;
	vector<string> result;

	while (getline(stream, field, delimiter))
	{
		result.push_back(field);
	}

	return result;
}