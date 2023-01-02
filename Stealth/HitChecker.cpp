#include "HitChecker.h"
#include "Player.h"
#include "Ball.h"
#include "Map.h"
#include "PreCompiledHeader.h"
#include <math.h>


HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, possessionBoal(false)
{
	//�����Ȃ�
}

HitChecker::~HitChecker()
{
	//�����Ȃ�
}

/// <summary>
/// �Փ˔���
/// </summary>
/// <param name="player"></param>
/// <param name="ball"></param>
void HitChecker::Check(Player* player, Ball* ball, Map* map)
{
	BallAndPlayer(player, ball);
	MapAndPlayer(map);
}

/// <summary>
/// �{�[���ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="player"></param>
/// <param name="ball"></param>
void HitChecker::BallAndPlayer(Player* player, Ball* ball)
{
	//�v���C���[����{�[���̍��W���������l���擾
	double posX = player->GetPosition().x - ball->GetPosition().x;
	double posZ = player->GetPosition().z - ball->GetPosition().z;

	//�v���C���[�ƃ{�[����2�_�Ԃ̋������v�Z
	direction = sqrt(pow(posX, 2) + pow(posZ, 2));
	
	//�{�[�����������Ă��Ȃ��Ȃ��
	//if (!possessionBoal)
	{
		if (direction < PLAYER_RADIUS + BALL_RADIUS)
		{
			hit = true;
		}
		else
		{
			hit = false;
		}
	}
	
}

void HitChecker::MapAndPlayer(Map* map)
{
}