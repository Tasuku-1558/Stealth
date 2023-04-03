#include "HitChecker.h"
#include "PreCompiledHeader.h"

#include "Player.h"
#include "Enemy.h"
#include "CakeBullet.h"
#include "GoalFlag.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
HitChecker::HitChecker()
	: hitPolyDim()
	, uiPosition()
	, uiHit(false)
	, pushBack()
	, mapHit(false)
	, flagHit(false)
	, UI_POSITION({ 0.0f, 30.0f, 800.0f })
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
/// <param name="model">�X�e�[�W���f��</param>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="cakeBullet">�P�[�L�o���b�g�̃|�C���^</param>
/// <param name="goalFlag">�S�[���I�u�W�F�N�g�̃|�C���^</param>
void HitChecker::Check(int model, Player* player, vector<CakeBullet*>* cakeBullet, /*vector<Enemy*>* enemy,*/ GoalFlag* goalFlag)
{
	CakeAndPlayer(player, cakeBullet);
	//EnemyAndPlayer(player, enemy);
	PlayerAndUi(player);
	MapAndPlayer(model, player);
	FlagAndPlayer(goalFlag, player);
}

/// <summary>
/// �P�[�L�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="cakeBullet"></param>
void HitChecker::CakeAndPlayer(Player* player, vector<CakeBullet*>* cakeBullet)
{
	for (auto itr = cakeBullet->begin(); itr != cakeBullet->end(); ++itr)
	{
		//�v���C���[����P�[�L�̍��W���������l���擾
		VECTOR sub = player->GetPosition() - (*itr)->cake->GetPosition();

		//�v���C���[�ƃP�[�L�̋������v�Z
		float distance = VSize(sub);
		float radius = player->GetCollide().radius + (*itr)->cake->GetCollideRadius();

		//�Փ˂��Ă���Ȃ��
		if (distance <= radius)
		{
			//�P�[�L�̔���
			(*itr)->cake->HitCake();
		}
	}
}

/// <summary>
/// �G�l�~�[�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="enemy"></param>
void HitChecker::EnemyAndPlayer(Player* player, /*vector<Enemy*>* enemy*/Enemy* enemy)
{
	//for (auto itr = enemy->begin(); itr != enemy->end(); ++itr)
	{
		//�v���C���[����G�l�~�[�̍��W���������l���擾
		VECTOR sub = player->GetPosition() - /*(*itr)*/enemy->GetPosition();

		//�v���C���[�ƃG�l�~�[�̋������v�Z
		float distance = VSize(sub);
		float radius = player->GetCollide().radius + /*(*itr)*/enemy->GetCollideRadius();

		//�Փ˂��Ă���Ȃ��
		if (distance <= radius)
		{
			//�G�l�~�[�̔���
			/*(*itr)*/enemy->HitPlayer();
		}
	}
}

/// <summary>
/// �v���C���[��UI�摜�̓����蔻��
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
void HitChecker::PlayerAndUi(Player* player)
{
	//�v���C���[����UI�摜�̍��W���������l���擾
	VECTOR sub = player->GetPosition() - uiPosition;

	//�v���C���[��UI�摜�̋������v�Z
	float distance = VSize(sub);
	float radius = player->GetCollide().radius + 50.0f;

	//�Փ˂��Ă���Ȃ��
	if (distance <= radius)
	{
		uiHit = true;
	}
	else
	{
		uiHit = false;
	}
}

/// <summary>
/// �}�b�v�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="model">�X�e�[�W���f��</param>
/// <param name="player">�v���C���[�̃|�C���^</param>
void HitChecker::MapAndPlayer(int model, Player* player)
{
	//���f���S�̂̃R���W���������\�z
	MV1SetupCollInfo(model, 0, 8, 8, 8);

	//�}�b�v���f���ƃv���C���[�̓����蔻��
	hitPolyDim = MV1CollCheck_Sphere(model, -1, player->GetCollide().worldCenter, player->GetCollide().radius);

	VECTOR moveCandidate = player->GetCollide().worldCenter;	//�����S���
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);					//�ړ��x�N�g��
	VECTOR planeNormal = VGet(0.0f, 0.0f, 0.0f);				//�|���S�����ʖ@��
	VECTOR newCenter = player->GetCollide().worldCenter;		//�ړ����
	float  moveLengh = 0.0f;									//�ړ���

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

			//�v���C���[���S�ɍł��߂��|���S�����ʂ̓_�����߂�
			VECTOR tmp = moveCandidate - hitPolyDim.Dim[i].Position[0];
			float  dot = VDot(planeNormal, tmp);

			//�Փ˓_
			VECTOR hitPos = moveCandidate - planeNormal * dot;

			//�v���C���[���ǂꂭ�炢�߂荞��ł��邩���Z�o
			VECTOR tmp2 = moveCandidate - hitPos;
			float  len = VSize(tmp2);

			//�߂荞��ł���ꍇ�̓v���C���[�̒��S�������߂�
			if (HitCheck_Sphere_Triangle(moveCandidate, player->GetCollide().radius,
				hitPolyDim.Dim[i].Position[0],
				hitPolyDim.Dim[i].Position[1],
				hitPolyDim.Dim[i].Position[2]))
			{
				//�߂荞�݉�������ʒu�܂ňړ�
				VECTOR moveVec;
				len = player->GetCollide().radius - len;
				moveVec = planeNormal * len;
				moveCandidate += moveVec;
			}

			//�ړ������ړ��ʒu�ɂ���
			newCenter = moveCandidate;

			pushBack = newCenter - player->GetDirection() + VScale(player->GetDirection(), 10.0f);
		}
	}
	else
	{
		mapHit = false;
	}
}

/// <summary>
/// �S�[���I�u�W�F�N�g�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="goalFlag"></param>
/// <param name="player">�v���C���[�̃|�C���^</param>
void HitChecker::FlagAndPlayer(GoalFlag* goalFlag, Player* player)
{
	//�v���C���[����S�[�����̍��W���������l���擾
	VECTOR sub = player->GetPosition() - goalFlag->GetPosition();

	//�v���C���[�ƃS�[���I�u�W�F�N�g�̋������v�Z
	float distance = VSize(sub);

	float radius = player->GetCollide().radius + goalFlag->GetCollideRadius();

	//�Փ˂��Ă���Ȃ��
	if (distance <= radius)
	{
		flagHit = true;
	}
	else
	{
		flagHit = false;
	}
}