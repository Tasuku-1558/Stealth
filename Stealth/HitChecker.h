#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Cake;

namespace My3dLib
{
	//���̓����蔻��
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void Move(const VECTOR& pos);

		VECTOR localCenter; //���̂̃��[�J�����S���W
		VECTOR worldCenter; //���̂̃��[���h���S���W
		float  radius;      //���̂̔��a
	};

	//�����蔻��̊֐��g�ݍ��킹
	bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);

}

/// <summary>
/// �����蔻��N���X
/// </summary>
class HitChecker final
{
public:
	HitChecker();
	virtual ~HitChecker();

	void Check(int model, Player* player, VECTOR flagPos);	//�Փ˔���
	void CakeAndPlayer(VECTOR playerPos, Cake* cake);		//�P�[�L�ƃv���C���[�̓����蔻��
	void EnemyAndPlayer(VECTOR playerPos, VECTOR enemyPos);	//�G�l�~�[�ƃv���C���[�̓����蔻��


	const bool CakeHit() { return cakeHit; }				//�P�[�L�Ƀv���C���[�������������ǂ�����Ԃ�
	const bool EnemyHit() { return enemyHit; }				//�G�l�~�[�Ƀv���C���[�������������ǂ�����Ԃ�
	const bool UI() { return uiDraw; }						//UI�摜�ɓ����������ǂ�����Ԃ�
	const bool MapHit() { return mapHit; }					//�}�b�v�Ƀv���C���[���Փ˂������ǂ�����Ԃ�
	const bool FlagHit() { return flagHit; }				//�S�[�����Ƀv���C���[�������������ǂ�����Ԃ�
	const VECTOR Back() { return pushBack; }				//�}�b�v�̕ǂɃv���C���[���Փ˂����Ƃ��̉����߂��l��Ԃ�

private:

	HitChecker(const HitChecker&);							//�R�s�[�R���X�g���N�^

	void PlayerAndUI(Player* player);						//�v���C���[��UI�摜�̓����蔻��
	void MapAndPlayer(int model, Player* player);			//�}�b�v�ƃv���C���[�̓����蔻��
	void FlagAndPlayer(VECTOR flagPos, Player* player);		//�S�[�����ƃv���C���[�̓����蔻��


	bool cakeHit;			//�P�[�L�ɏՓ˂����Ȃ��
	bool enemyHit;			//�G�l�~�[�ƏՓ˂����Ȃ��
	VECTOR uiPosition;		//UI�摜�̈ʒu
	bool uiDraw;			//UI�摜��`�悷�邩�ǂ���
	bool flagHit;			//�S�[�����ɏՓ˂����Ȃ��

	bool mapHit;			//�}�b�v���f���ɏՓ˂����Ȃ��
	VECTOR pushBack;		//�}�b�v�ɏՓ˂������̉����߂���

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

	//�萔
	const VECTOR UI_POSITION;	//UI�摜�̈ʒu

};