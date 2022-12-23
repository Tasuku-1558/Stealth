#include "HitChecker.h"
#include "Player.h"
#include "Boal.h"
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

//�Փ˔���
void HitChecker::Check(Player* player, Boal* boal)
{
	BoalAndPlayer(player, boal);
}

//�{�[���ƃv���C���[�̓����蔻��
void HitChecker::BoalAndPlayer(Player* player, Boal* boal)
{
	
	//�v���C���[����{�[���̍��W���������l���擾
	double posX = player->GetPosition().x - boal->GetPosition().x;
	double posZ = player->GetPosition().z - boal->GetPosition().z;

	//�v���C���[�ƃ{�[����2�_�Ԃ̋������v�Z
	direction = sqrt(pow(posX, 2) + pow(posZ, 2));
	
	//�{�[�����������Ă��Ȃ��Ȃ��
	//if (!possessionBoal)
	{
		if (direction < PLAYER_RADIUS + BOAL_RADIUS)
		{
			printfDx("hit");
			hit = true;
		}
		else
		{
			hit = false;
		}
	}
	
}