#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Wall;
class Ball;


/// <summary>
/// �q�b�g�`�F�b�J�[�N���X
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	 virtual ~HitChecker();

	void Check(int model, Player* player);							//�Փ˔���
	void BallAndPlayer(VECTOR playerPos, Ball* ball);			//�{�[���ƃv���C���[�̓����蔻��


	bool UI() { return uiDraw; }
	VECTOR Back() { return pushBack; }								//�}�b�v�̕ǂɃv���C���[���Փ˂����Ƃ��̉����߂��l��Ԃ�
	bool MapHit() { return mapHit; }								//�}�b�v���v���C���[���Փ˂����Ȃ��

private:

	HitChecker(const HitChecker&);							//�R�s�[�R���X�g���N�^

	void PlayerAndUI(Player* player);						//�v���C���[��UI�摜�̓����蔻��
	void MapAndPlayer(int model, Player* player);


	bool ballHit;			//�{�[���ɏՓ˂����Ȃ��
	VECTOR uiPos;			//UI�摜�̈ʒu
	bool uiDraw;			//UI�摜��`�悷�邩�ǂ���

	bool mapHit;			//�}�b�v���f���ɏՓ˂����Ȃ��
	VECTOR pushBack;

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};