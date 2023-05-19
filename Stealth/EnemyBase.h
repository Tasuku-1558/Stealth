#pragma once

#include <string>
#include <vector>
#include "ObjectBase.h"

using namespace std;

/// <summary>
/// �G�l�~�[���N���X
/// </summary>
class EnemyBase : public ObjectBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

protected:

	vector<VECTOR>& GetList(int number) { return positionList[number]; }      //�G�̍s���p�^�[�����X�g��Ԃ�

	int markImage;					//�r�b�N���}�[�N�摜�i�[�p
	int visualModelHandle;			//���샂�f���n���h��
	float speed;					//�G�l�~�[�̈ړ����x
	float changeSpeed;				//�X�e�[�W���Ƃ̃G�l�~�[�̈ړ����x
	float playerDirection;			//�v���C���[�ƃG�l�~�[�̋���
	float bulletDirection;			//�o���b�g�ƃG�l�~�[�̋���
	float rotateTime;				//��]����
	bool playerSpotted;				//�v���C���[�𔭌��������ǂ���
	bool cakeFlag;					//�P�[�L�𔭌��������ǂ���
	VECTOR targetPosition;			//�ړI�n�̍��W
	VECTOR visualPosition;			//���샂�f���̈ʒu
	VECTOR visualDir;				//���샂�f���̕���


	//�萔
	const int	 ROTATE_TIME_CATEGORY;	//��]���Ԃ̎��
	const float  RANGE_DEGREE;			//����p�x
	const float  LENGTH;				//����p�̋���
	const float  TARGET_ANGLE;			//��]�̖ڕW�p�x
	const float  INITIAL_ROTATE_TIME;	//�����̉�]����
	const float  RADIUS;				//�G�l�~�[�̔��a
	const float	 Y_ANGLE;				//Y���̉�]�l
	const float  Y_ANGLE_SPEED;			//Y����]�X�s�[�h
	const float  NOMAL_ROTATE_TIME;		//�ʏ�̉�]����
	const float  PLAYER_ROTATE_TIME;	//�v���C���[���������̉�]����
	const float  CAKE_ROTATE_TIME;		//�P�[�L���������̉�]����
	const float  STOP_SPEED;			//�G�l�~�[�̈ړ����x���~������
	const string IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string MARK_PATH;				//�r�b�N���}�[�N�摜�̃p�X
	
private:
	EnemyBase(const EnemyBase&);		//�R�s�[�R���X�g���N�^

	//FirstStage�ł̓G�̍s��
	void MapList();                     //�G�̍s���p�^�[�����X�g(���E�ړ��̓G)

	//SecondStage�ł̓G�̍s��
	void MapList2();                    //�G�̍s���p�^�[�����X�g2(�ǂ̎�������G)
	void MapList3();                    //�G�̍s���p�^�[�����X�g3(�㉺�ړ��̓G)

	vector<VECTOR> positionList[9];
	vector<VECTOR>::iterator itr[9];

};