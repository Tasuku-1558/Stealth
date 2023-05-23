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
	FILE* filePointer = nullptr;								//�t�@�C���̃|�C���^��錾
	fopen_s(&filePointer, "Data/Csv/Stage1.csv", "r");			//fopen_s�֐���csv��ǂݎ��`���ŊJ��

	if (filePointer == NULL)									//filePointer����̏ꍇ��
	{
		DebugBreak();											//�f�o�b�O���~
	}

	memset(buffer, 0, sizeof(buffer));							//memset�֐��Ń�������buffer���Z�b�g���Asizeof���Z�q�ŗv�f�������߂�

	while (1)
	{
		while (1)
		{
			characterPack = fgetc(filePointer);										//fgetc�֐���filepointer���當����ǂ��characterPack�Ɋi�[
			if (characterPack == EOF)
			{
				endFlag = true;														//EndOfFile�����o����
				break;																//���[�v�𔲂���
			}
			if (characterPack != ',' && characterPack != '\n')						//��؂肩���s�łȂ����
			{
				strcat_s(buffer, (const char*)&characterPack);						//strcat_s�֐���buffer�ɘA�����Aconst char�֐��ŏ���������
			}
			else
			{
				num = atoi(buffer);													//atoi�֐���buffer��int�^�ɒ����āA���[�J���ϐ�num�ɑ��
				s[columnNum][rawNum] = stageHandle[num];			//num�Ԗڂ̃`�b�v�摜�̃n���h�����擾
				memset(buffer, 0, sizeof(buffer));									//buffer�����Z�b�g
				break;																//��؂肩���s�Ȃ̂Ń��[�v�𔲂���
			}
		}
		if (endFlag)																//1�}�b�v���ɂȂ�����
		{
			break;																	//���[�v�𔲂���
		}
		if (characterPack == ',')													//��؂�����o������
		{
			columnNum++;															//��̐��𑝂₷
		}
		if (characterPack == '\n')													//���s��������
		{
			rawNum++;																//�s�𑝂₷
			columnNum = 0;															//���0�ɂ���
		}
	}

	fclose(filePointer);															//�t�@�C�������
}

StageData::~StageData()
{
	//�����Ȃ�
}