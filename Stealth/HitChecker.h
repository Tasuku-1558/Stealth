#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Enemy;
class Cake;
class GoalFlag;

/// <summary>
/// �����蔻��N���X
/// </summary>
class HitChecker final
{
public:
	HitChecker();
	virtual ~HitChecker();

	void Check(int model, Player* player, GoalFlag* goalFlag);	//�Փ˔���
	void CakeAndPlayer(Player* player, Cake* cake);			//�P�[�L�ƃv���C���[�̓����蔻��
	void EnemyAndPlayer(Player* player, Enemy* enemy);	//�G�l�~�[�ƃv���C���[�̓����蔻��


	const bool UI() { return uiHit; }						//UI�摜�ɓ����������ǂ�����Ԃ�
	const bool MapHit() { return mapHit; }					//�}�b�v�Ƀv���C���[���Փ˂������ǂ�����Ԃ�
	const bool FlagHit() { return flagHit; }				//�S�[�����Ƀv���C���[�������������ǂ�����Ԃ�
	const VECTOR Back() { return pushBack; }				//�}�b�v�̕ǂɃv���C���[���Փ˂����Ƃ��̉����߂��l��Ԃ�

private:

	HitChecker(const HitChecker&);							//�R�s�[�R���X�g���N�^

	void PlayerAndUI(Player* player);						//�v���C���[��UI�摜�̓����蔻��
	void MapAndPlayer(int model, Player* player);			//�}�b�v�ƃv���C���[�̓����蔻��
	void FlagAndPlayer(GoalFlag* goalFlag, Player* player);		//�S�[�����ƃv���C���[�̓����蔻��


	VECTOR uiPosition;		//UI�摜�̈ʒu
	bool uiHit;				//UI�摜��`�悷�邩�ǂ���
	bool flagHit;			//�S�[�����ɏՓ˂������ǂ���
	bool mapHit;			//�}�b�v���f���ɏՓ˂������ǂ���
	VECTOR pushBack;		//�}�b�v�ɏՓ˂������̉����߂���

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

	//�萔
	const VECTOR UI_POSITION;	//UI�摜�̈ʒu

};