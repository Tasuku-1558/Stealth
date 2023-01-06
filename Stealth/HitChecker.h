#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Ball;
class Map;
class Wall;
class Enemy;


/// <summary>
/// �q�b�g�`�F�b�J�[�N���X
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();

	void Check(Player* player, Ball* ball, Map* map);			//�Փ˔���
	bool Hit() { return hit; }

	VECTOR ai() { return a; }
	bool hita() { return aio; }

private:

	HitChecker(const HitChecker&);		//�R�s�[�R���X�g���N�^

	void BallAndPlayer(Player* player, Ball* ball);			//�{�[���ƃv���C���[�̓����蔻��
	void MapAndPlayer(Map* map, Player* player);
	void WallAndEnemy(Wall* wall, Enemy* enemy);

	double direction;
	bool hit;				//�Փ˂����Ȃ��
	bool possessionBoal;	//�������Ă���{�[���̐�

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;
	VECTOR a;
	bool aio;

};