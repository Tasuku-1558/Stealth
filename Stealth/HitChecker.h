#pragma once

#include "DxLib.h"

class Player;
class Ball;
class Map;


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


private:

	HitChecker(const HitChecker&);		//�R�s�[�R���X�g���N�^

	void BallAndPlayer(Player* player, Ball* ball);			//�{�[���ƃv���C���[�̓����蔻��
	void MapAndPlayer(Map* map);

	double direction;
	bool hit;				//�Փ˂����Ȃ��
	bool possessionBoal;	//�������Ă���{�[���̐�

};