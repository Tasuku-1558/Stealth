#include "HitChecker.h"
#include "PreCompiledHeader.h"

#include "Player.h"
#include "Cake.h"


using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
HitChecker::HitChecker()
	: cakeHit(false)
	, hitPolyDim()
	, uiPosition()
	, uiDraw(false)
	, pushBack()
	, mapHit(false)
	, enemyHit(false)
	, UI_POSITION({ -800.0f, 30.0f, 0.0f })
{
	uiPosition = UI_POSITION;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HitChecker::~HitChecker()
{
	//�����Ȃ�
}

/// <summary>
/// �Փ˔���
/// </summary>
/// <param name="model"></param>
/// <param name="player"></param>
void HitChecker::Check(int model, Player* player, VECTOR flagPos)
{
	PlayerAndUI(player);
	MapAndPlayer(model, player);
	FlagAndPlayer(flagPos, player);
}

/// <summary>
/// �P�[�L�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="playerPos"></param>
/// <param name="cake"></param>
void HitChecker::CakeAndPlayer(VECTOR playerPos, Cake* cake)
{
	//�v���C���[����P�[�L�̍��W���������l���擾
	VECTOR sub = playerPos - cake->GetPosition();

	//�v���C���[�ƃP�[�L��2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));
	
	//�Փ˂��Ă���Ȃ��
	if (direction < PLAYER_RADIUS + CAKE_RADIUS)
	{
		cakeHit = true;
	}
	else
	{
		cakeHit = false;
	}
}

/// <summary>
/// �G�l�~�[�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="playerPos"></param>
/// <param name="monitoringEnemy"></param>
void HitChecker::EnemyAndPlayer(VECTOR playerPos, VECTOR enemyPos)
{
	//�v���C���[����P�[�L�̍��W���������l���擾
	VECTOR sub = playerPos - enemyPos;

	//�v���C���[�ƃP�[�L��2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�Փ˂��Ă���Ȃ��
	if (direction < PLAYER_RADIUS + ENEMY_RADIUS)
	{
		enemyHit = true;
	}
	else
	{
		enemyHit = false;
	}
}

/// <summary>
/// �v���C���[��UI�摜�̓����蔻��
/// </summary>
/// <param name="player"></param>
void HitChecker::PlayerAndUI(Player* player)
{
	//�v���C���[����UI�摜�̍��W���������l���擾
	VECTOR sub = player->GetPosition() - uiPosition;

	//�v���C���[��UI�摜��2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�Փ˂��Ă���Ȃ��
	if (direction < PLAYER_RADIUS + 50.0f)
	{
		uiDraw = true;
	}
	else
	{
		uiDraw = false;
	}
}

/// <summary>
/// �}�b�v�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="model"></param>
/// <param name="player"></param>
void HitChecker::MapAndPlayer(int model, Player* player)
{
	//���f���S�̂̃R���W���������\�z
	MV1SetupCollInfo(model, 0, 8, 8, 8);

	//�}�b�v���f���ƃv���C���[�̓����蔻��
	hitPolyDim = MV1CollCheck_Sphere(model, -1, player->GetPosition(), 100.0f);

	VECTOR moveCandidate = player->GetPosition(); //�����S���

	VECTOR moveVec = VGet(0, 0, 0);    //�ړ��x�N�g��
	float  moveLengh = 0.0f;           //�ړ���
	VECTOR planeNormal = VGet(0, 0, 0);    //�|���S�����ʖ@��

	VECTOR newCenter = player->GetPosition(); //�ړ����
	

	//�v���C���[���}�b�v�ɓ����������ǂ���
	if (hitPolyDim.HitNum)
	{	
		mapHit = true;

		//�Փ˃|���S�������ׂĉ���āA���̂߂荞�݂�����
		for (int i = 0; i < hitPolyDim.HitNum; ++i)
		{
			//�Փ˃|���S���̕� 
			VECTOR edge1 = hitPolyDim.Dim[i].Position[1] - hitPolyDim.Dim[i].Position[0];
			VECTOR edge2 = hitPolyDim.Dim[i].Position[2] - hitPolyDim.Dim[i].Position[0];

			//�Փ˃|���S���̕ӂ��A�|���S���ʂ̖@���x�N�g�������߂�
			planeNormal = VCross(edge1, edge2);
			planeNormal = VNorm(planeNormal);

			//�����S�ɍł��߂��|���S�����ʂ̓_�����߂�
			VECTOR tmp = moveCandidate - hitPolyDim.Dim[i].Position[0];
			float  dot = VDot(planeNormal, tmp);

			//�Փ˓_
			VECTOR hitPos = moveCandidate - planeNormal * dot;

			//�����ǂꂭ�炢�߂荞��ł��邩���Z�o
			VECTOR tmp2 = moveCandidate - hitPos;
			float  len = VSize(tmp2);

			//�߂荞��ł���ꍇ�͋��̒��S�������߂�
			if (HitCheck_Sphere_Triangle(moveCandidate, PLAYER_RADIUS,
				hitPolyDim.Dim[i].Position[0],
				hitPolyDim.Dim[i].Position[1],
				hitPolyDim.Dim[i].Position[2]))
			{
				//�߂荞�݉�������ʒu�܂ňړ�
				VECTOR moveVec;
				len = PLAYER_RADIUS - len;
				moveVec = planeNormal * len;
				moveCandidate += moveVec;
			}

			//�ړ������ړ��ʒu�ɂ���
			newCenter = moveCandidate;

			pushBack = newCenter - player->GetDir() + VScale(player->GetDir(), 10.0f);
		}
	}
	else
	{
		mapHit = false;
	}
}

/// <summary>
/// �S�[�����ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="flagPos"></param>
/// <param name="player"></param>
void HitChecker::FlagAndPlayer(VECTOR flagPos, Player* player)
{
	//�v���C���[����S�[�����̍��W���������l���擾
	VECTOR sub = player->GetPosition() - flagPos;

	//�v���C���[�ƃS�[������2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�Փ˂��Ă���Ȃ��
	if (direction < PLAYER_RADIUS + 50.0f)
	{
		flagHit = true;
	}
	else
	{
		flagHit = false;
	}
}