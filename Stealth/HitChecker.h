#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Wall;


/// <summary>
/// �q�b�g�`�F�b�J�[�N���X
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	 virtual ~HitChecker();

	void Check(int model, Player* player);							//�Փ˔���
	void BallAndPlayer(VECTOR playerPos, VECTOR ballPos);			//�{�[���ƃv���C���[�̓����蔻��


	bool Hit() { return hit; }
	bool UI() { return uiDraw; }

	bool MapHit() { return mapHit; }

private:

	HitChecker(const HitChecker&);		//�R�s�[�R���X�g���N�^

	void PlayerAndUI(Player* player);						//�v���C���[��UI�摜�̓����蔻��
	void MapAndPlayer(int model, Player* player);


	bool hit;				//�Փ˂����Ȃ��
	VECTOR uiPos;
	bool uiDraw;

	bool mapHit;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};