#include "HitChecker.h"
#include "Player.h"
#include "Ball.h"
#include "Map.h"
#include "PreCompiledHeader.h"


using namespace Math3d;

HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, possessionBoal(false)
	, HitPolyDim()
	, a(false)
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
	MapAndPlayer(map, player);
}

/// <summary>
/// �{�[���ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="player"></param>
/// <param name="ball"></param>
void HitChecker::BallAndPlayer(Player* player, Ball* ball)
{
	//�v���C���[����{�[���̍��W���������l���擾
	VECTOR sub = player->GetPosition() - ball->GetPosition();

	//�v���C���[�ƃG�l�~�[��2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));
	
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

void HitChecker::MapAndPlayer(Map* map, Player* player)
{

	// ���f���S�̂̃R���W���������\�z
	MV1SetupCollInfo(map->GetModel(), -1, 8, 8, 8);

	// ���f���Ƌ��Ƃ̓����蔻��
	HitPolyDim = MV1CollCheck_Sphere(map->GetModel(), -1, player->GetPosition(), 100.0f);

	// �����������ǂ����ŏ����𕪊�
	if (HitPolyDim.HitNum >= 1)
	{

		printfDx("hit");
		a = true;
		HitPolyDim.HitNum = 0;
	}
	else
	{
		a = false;
	}
}