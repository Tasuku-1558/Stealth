#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Ball;
class Map;
class Wall;


/// <summary>
/// �q�b�g�`�F�b�J�[�N���X
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();

	void Check(int model, Player* player, Ball* ball);			//�Փ˔���

	void MapAndPlayer(int model, Player* player);

	bool Hit() { return hit; }
	bool UI() { return uiDraw; }

private:

	HitChecker(const HitChecker&);		//�R�s�[�R���X�g���N�^

	void BallAndPlayer(Player* player, Ball* ball);			//�{�[���ƃv���C���[�̓����蔻��
	void PlayerAndUI(Player* player);						//�v���C���[��UI�摜�̓����蔻��

	bool hit;				//�Փ˂����Ȃ��
	VECTOR uiPos;
	bool uiDraw;

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};