#pragma once

#include "StageBase.h"
#include "ModelManager.h"
#include <vector>


/// <summary>
/// �X�e�[�W�}�b�v�N���X
/// </summary>
class StageMap final : public StageBase
{
public:
	StageMap(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position);
	virtual ~StageMap();

	void Initialize();      //����������
	void Draw();            //�`�揈��

	std::vector<VECTOR>& GetMap(int number) { return positionList[number]; }      //�G�̍s���p�^�[�����X�g��Ԃ�

private:
	StageMap(const StageMap&);				//�R�s�[�R���X�g���N�^

	void Finalize();						//�I������

	//FirstStage�ł̓G�̍s��
	void MapList();                         //�G�̍s���p�^�[�����X�g(���E�ړ��̓G)

	//SecondStage�ł̓G�̍s��
	void MapList2();                        //�G�̍s���p�^�[�����X�g2(�ǂ̎�������G)
	void MapList3();                        //�G�̍s���p�^�[�����X�g3(�㉺�ړ��̓G)

	//ThirdStage�ł̓G�̍s��
	void MapList4();                        //�G�̍s���p�^�[�����X�g4(�㉺�ړ��̓G)
	void MapList5();                        //�G�̍s���p�^�[�����X�g5(�S�[���̈ʒu���ǂ��G)

	//FourthStage�ł̓G�̍s��
	void MapList6();                        //�G�̍s���p�^�[�����X�g6(���E�ړ��̓G)
	void MapList7();                        //�G�̍s���p�^�[�����X�g7(�ǂ̎�������G)

	//FifthStage�ł̓G�̍s��
	void MapList8();                        //�G�̍s���p�^�[�����X�g8(�E��L���ړ��̓G)
	void MapList9();                        //�G�̍s���p�^�[�����X�g9(����L���ړ��̓G)

	std::vector<VECTOR> positionList[9];
	std::vector<VECTOR>::iterator itr[9];
};