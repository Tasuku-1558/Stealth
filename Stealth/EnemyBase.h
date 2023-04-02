#pragma once

#include "ObjectBase.h"
#include <vector>

/// <summary>
/// �G�l�~�[���N���X
/// </summary>
class EnemyBase : public ObjectBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

protected:

	std::vector<VECTOR>& GetList(int number) { return positionList[number]; }      //�G�̍s���p�^�[�����X�g��Ԃ�

	int markImage;					//�r�b�N���}�[�N�摜�i�[�p
	int visualModelHandle;			//���샂�f���n���h��
	float speed;					//�G�l�~�[�̈ړ����x
	float changeSpeed;				//�X�e�[�W���Ƃ̃G�l�~�[�̈ړ����x
	float length;					//����p�̋���
	float bulletDirection;			//�o���b�g�ƃG�l�~�[�̋���
	bool playerSpotted;				//�v���C���[�𔭌��������ǂ���
	bool cakeFlag;					//�P�[�L�𔭌��������ǂ���
	VECTOR targetPosition;			//�ړI�n�̍��W
	VECTOR visualPosition;			//���샂�f���̈ʒu
	VECTOR visualDir;				//���샂�f���̕���


	//�萔
	const float RANGE_DEGREE;		//����p�x
	const float RADIUS;				//�G�l�~�[�̔��a
	
private:

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