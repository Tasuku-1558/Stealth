#include "HitChecker.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Map.h"
#include "Wall.h"
#include "PreCompiledHeader.h"


using namespace Math3d;

HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, hitPolyDim()
	, a()
	, aio(false)
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
	MV1SetupCollInfo(map->GetModel(), 0, 8, 8, 8);

	// ���f���Ƌ��Ƃ̓����蔻��
	hitPolyDim = MV1CollCheck_Sphere(map->GetModel(), -1, player->GetPosition(), 100.0f);

	VECTOR moveCandidate = player->GetPosition(); // �����S��� 

	VECTOR moveVec = VGet(0, 0, 0);    // �ړ��x�N�g��
	float  moveLen = 0.0f;           // �ړ���
	VECTOR planeNormal;                    // �|���S�����ʖ@��

	VECTOR newCenter = player->GetPosition(); // �ړ����  
	
	aio = false;

	// �����������ǂ���
	if (hitPolyDim.HitNum)
	{
		printfDx("hit");

		aio = true;

		// �Փ˃|���S�������ׂĉ���āA���̂߂荞�݂�����
		for (int i = 0; i < hitPolyDim.HitNum; ++i)
		{
			// �Փ˃|���S���̕� 
			VECTOR edge1 = hitPolyDim.Dim[i].Position[1] - hitPolyDim.Dim[i].Position[0];
			VECTOR edge2 = hitPolyDim.Dim[i].Position[2] - hitPolyDim.Dim[i].Position[0];

			// �Փ˃|���S���̕ӂ��A�|���S���ʂ̖@���x�N�g�������߂�
			planeNormal = VCross(edge1, edge2);
			planeNormal = VNorm(planeNormal);

			// �����S�ɍł��߂��|���S�����ʂ̓_�����߂�
			VECTOR tmp = moveCandidate - hitPolyDim.Dim[i].Position[0];
			float  dot = VDot(planeNormal, tmp);

			// �Փ˓_
			VECTOR hitPos = moveCandidate - planeNormal * dot;

			// �����ǂꂭ�炢�߂荞��ł��邩���Z�o
			VECTOR tmp2 = moveCandidate - hitPos;
			float  len = VSize(tmp2);

			// �߂荞��ł���ꍇ�͋��̒��S�������߂�
			if (HitCheck_Sphere_Triangle(moveCandidate, PLAYER_RADIUS,
				hitPolyDim.Dim[i].Position[0],
				hitPolyDim.Dim[i].Position[1],
				hitPolyDim.Dim[i].Position[2]))
			{
				// �߂荞�݉�������ʒu�܂ňړ�
				VECTOR moveVec;
				len = PLAYER_RADIUS - len;
				moveVec = planeNormal * len;
				moveCandidate += moveVec;
			}

			// �ړ������ړ��ʒu�ɂ���
			newCenter = moveCandidate;

			a = newCenter - player->GetPosition();

		}

	}
	
}

void HitChecker::WallAndEnemy(Wall* wall, Enemy* enemy)
{
}