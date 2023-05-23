#pragma once

#include <vector>
#include "DxLib.h"
#include "Math3D.h"

#include "Stage.h"
#include "Player.h"
#include "CakeBullet.h"
#include "Enemy.h"
#include "GoalFlag.h"

using namespace std;

/// <summary>
/// �����蔻��N���X
/// </summary>
class HitChecker final
{
public:
	HitChecker();
	virtual ~HitChecker();

	void Check(float deltaTime,
			   vector<Stage*>* stage,
			   Player* player,
			   vector<CakeBullet*>* cakeBullet,
			   vector<Enemy*>* enemy,
			   GoalFlag* goalFlag);				//�Փ˔���

	const bool UiHit() { return uiHit; }		//Ui�摜�ɓ����������ǂ�����Ԃ�
	const bool GoalHit() { return flagHit; }	//�S�[���I�u�W�F�N�g�ɓ����������ǂ�����Ԃ�

private:
	HitChecker(const HitChecker&);				//�R�s�[�R���X�g���N�^

	void CakeAndPlayer(Player* player, vector<CakeBullet*>* cakeBullet);	//�P�[�L�ƃv���C���[�̓����蔻��
	void EnemyAndPlayer(Player* player, vector<Enemy*>* enemy);				//�G�l�~�[�ƃv���C���[�̓����蔻��
	void PlayerAndUi(Player* player);										//�v���C���[��Ui�摜�̓����蔻��
	void MapAndPlayer(vector<Stage*>* stage, Player* player);				//�}�b�v�ƃv���C���[�̓����蔻��
	void FlagAndPlayer(GoalFlag* goalFlag, Player* player);					//�S�[���I�u�W�F�N�g�ƃv���C���[�̓����蔻��

	void VisualAngleCake(float deltaTime, vector<Enemy*>* enemy, vector<CakeBullet*>* cakeBullet);	//�G�l�~�[�̎���ɃP�[�L���������ꍇ
	void VisualAnglePlayer(Player* player, vector<Enemy*>* enemy);									//�G�l�~�[�̎���Ƀv���C���[���������ꍇ


	float moveLengh;		//�ړ���
	bool uiHit;				//Ui�摜��`�悷�邩�ǂ���
	bool flagHit;			//�S�[���I�u�W�F�N�g�ɏՓ˂������ǂ���
	VECTOR uiPosition;		//Ui�摜�̈ʒu
	VECTOR pushBack;		//�}�b�v�ɏՓ˂������̉����߂���
	VECTOR moveVec;			//�ړ��x�N�g��
	VECTOR planeNormal;		//�|���S�����ʖ@��

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;	//�R���W�������ʑ���p�|���S���z��

	//�萔
	const int	 FRAME_INDEX;	//�����蔻������X�V����t���[���̔ԍ�
	const int	 DIV_NUMBER;	//�R���W�������̎������̋�ԕ�����
	const float  RANGE_DEGREE;	//����p�x
	const float  RANGE_HALF;	//�����̎���͈�
	const float  LENGTH;		//����p�̋���
	const float  SCALE;			//�X�P�[�����O�l
	const VECTOR UI_POSITION;	//Ui�摜�̈ʒu

};