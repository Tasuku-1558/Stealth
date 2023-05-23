#pragma once
#include "PreCompiledHeader.h"

/// <summary>
/// �X�e�[�WCSV�ǂݍ��݃N���X
/// </summary>
class StageData final
{
public:
	StageData();
	virtual ~StageData();

	int s[BLOCK_NUM_X][BLOCK_NUM_Z];


private:
	StageData(const StageData&);		//�R�s�[�R���X�g���N�^

	int stageHandle[256];

	int characterPack;				//�������i�[����ϐ�
	int rawNum;					//�������̃^�C���i���o�[
	int columnNum;				//�c�����̃^�C���i���o�[
	int num;						//�^�C���̔ԍ�
	char buffer[10];				//������ϐ�
	bool endFlag;			//eof�iend of file�j���o�t���O

};