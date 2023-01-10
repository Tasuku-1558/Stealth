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

	void Check(Player* player, Ball* ball, Map* map, Enemy* enemy);			//�Փ˔���
	bool Hit() { return hit; }
	bool UI() { return uiDraw; }

private:

	HitChecker(const HitChecker&);		//�R�s�[�R���X�g���N�^

	void BallAndPlayer(Player* player, Ball* ball);			//�{�[���ƃv���C���[�̓����蔻��
	void PlayerAndUI(Player* player);
	void MapAndPlayer(Map* map, Player* player);
	void WallAndEnemy(Wall* wall, Enemy* enemy);
	void BulletAndEnemy(Player* player, Enemy* enemy);

	bool hit;				//�Փ˂����Ȃ��
	VECTOR uiPos;
	bool uiDraw;

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};