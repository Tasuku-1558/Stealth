#include "StageData.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="csvName">CSV�t�@�C���̖��O</param>
StageData::StageData(const char* csvName)
	: stageNum()
{
	ifstream ifs(csvName);

	string line;

	//�ǂݍ��ݎ��s�Ȃ�G���[
	if (!ifs)
	{
		printfDx("CSV�t�@�C���̓ǂݍ��݂Ɏ��s[%s]\n", csvName);
	}

	//CSV�t�@�C���̍Ō�̍s�܂ŉ�
	while (getline(ifs, line))
	{
		strvec = Split(line, ',');

		for (int i = 0; i < strvec.size(); i++)
		{
			//�����^�֕ϊ�
			stageNum[i] = stoi(strvec.at(i));
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

/// <summary>
/// CSV�t�@�C���̒l�̓ǂݍ���
/// </summary>
/// <param name="input">string�ϐ��i�[</param>
/// <param name="delimiter">�J���}�����i�[</param>
/// <returns>�ǂݍ��񂾒l��Ԃ�</returns>
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