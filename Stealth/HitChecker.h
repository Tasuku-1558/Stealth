#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Cake;

/// <summary>
/// �����蔻��N���X
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	 virtual ~HitChecker();

	void Check(int model, Player* player);					//�Փ˔���
	void BallAndPlayer(VECTOR playerPos, Cake* cake);		//�P�[�L�ƃv���C���[�̓����蔻��
	void EnemyAndPlayer(VECTOR playerPos, VECTOR enemyPos);	//�G�l�~�[�ƃv���C���[�̓����蔻��


	const bool CakeHit() { return cakeHit; }				//�P�[�L�Ƀv���C���[�������������ǂ�����Ԃ�
	const bool EnemyHit() { return enemyHit; }				//�G�l�~�[�Ƀv���C���[�������������ǂ�����Ԃ�
	const bool UI() { return uiDraw; }						//UI�摜�ɓ����������ǂ�����Ԃ�
	const VECTOR Back() { return pushBack; }				//�}�b�v�̕ǂɃv���C���[���Փ˂����Ƃ��̉����߂��l��Ԃ�
	const bool MapHit() { return mapHit; }					//�}�b�v���v���C���[���Փ˂������ǂ�����Ԃ�

private:

	HitChecker(const HitChecker&);							//�R�s�[�R���X�g���N�^

	void PlayerAndUI(Player* player);						//�v���C���[��UI�摜�̓����蔻��
	void MapAndPlayer(int model, Player* player);			//�}�b�v�ƃv���C���[�̓����蔻��


	bool cakeHit;			//�P�[�L�ɏՓ˂����Ȃ��
	bool enemyHit;			//�G�l�~�[�ƏՓ˂����Ȃ��
	VECTOR uiPosition;		//UI�摜�̈ʒu
	bool uiDraw;			//UI�摜��`�悷�邩�ǂ���

	bool mapHit;			//�}�b�v���f���ɏՓ˂����Ȃ��
	VECTOR pushBack;		//�}�b�v�ɏՓ˂������̉����߂���

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

	//�ÓI�萔
	static const VECTOR UI_POSITION;	//UI�摜�̈ʒu

};