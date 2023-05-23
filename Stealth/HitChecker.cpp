#include "HitChecker.h"
#include "PreCompiledHeader.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
HitChecker::HitChecker()
	: moveLengh(0.0f)
	, uiHit(false)
	, flagHit(false)
	, uiPosition()
	, pushBack()
	, moveVec()
	, planeNormal()
	, hitPolyDim()
	, DIV_NUMBER(8)
	, FRAME_INDEX(-1)
	, RANGE_DEGREE(27.0f)
	, RANGE_HALF(2.0f)
	, LENGTH(900.0f)
	, SCALE(10.0f)
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
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
/// <param name="stageBlock">�X�e�[�W�u���b�N�̃|�C���^</param>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="cakeBullet">�P�[�L�o���b�g�̃|�C���^</param>
/// <param name="enemy">�G�l�~�[�̃|�C���^</param>
/// <param name="goalFlag">�S�[���I�u�W�F�N�g�̃|�C���^</param>
void HitChecker::Check(float deltaTime, vector<StageBlock*>* stageBlock, Player* player, vector<CakeBullet*>* cakeBullet, vector<Enemy*>* enemy, GoalFlag* goalFlag)
{
	MapAndPlayer(stageBlock, player);
	CakeAndPlayer(player, cakeBullet);
	EnemyAndPlayer(player, enemy);
	PlayerAndUi(player);
	FlagAndPlayer(goalFlag, player);

	VisualAngleCake(deltaTime, enemy, cakeBullet);
	VisualAnglePlayer(player, enemy);
}

/// <summary>
/// �P�[�L�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="cakeBullet">�P�[�L�o���b�g�̃|�C���^</param>
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
/// <param name="enemy">�G�l�~�[�̃|�C���^</param>
void HitChecker::EnemyAndPlayer(Player* player, vector<Enemy*>* enemy)
{
	for (auto itr = enemy->begin(); itr != enemy->end(); ++itr)
	{
		//�v���C���[����G�l�~�[�̍��W���������l���擾
		VECTOR sub = player->GetPosition() - (*itr)->GetPosition();

		//�v���C���[�ƃG�l�~�[�̋������v�Z
		float distance = VSize(sub);
		float radius = player->GetCollide().radius + (*itr)->GetCollideRadius();

		//�Փ˂��Ă���Ȃ��
		if (distance <= radius)
		{
			//�G�l�~�[�̔���
			(*itr)->HitPlayer();
		}
	}
}

/// <summary>
/// �v���C���[��Ui�摜�̓����蔻��
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
void HitChecker::PlayerAndUi(Player* player)
{
	//�v���C���[����Ui�摜�̍��W���������l���擾
	VECTOR sub = player->GetPosition() - uiPosition;

	//�v���C���[��Ui�摜�̋������v�Z
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
/// <param name="stageBlock">�X�e�[�W�u���b�N�̃|�C���^</param>
/// <param name="player">�v���C���[�̃|�C���^</param>
void HitChecker::MapAndPlayer(vector<StageBlock*>* stageBlock, Player* player)
{
	for (auto itr = stageBlock->begin(); itr != stageBlock->end(); ++itr)
	{
		//���f���S�̂̃R���W���������\�z
		MV1SetupCollInfo((*itr)->GetModelHandle(), FRAME_INDEX, DIV_NUMBER, DIV_NUMBER, DIV_NUMBER);

		//�X�e�[�W���f���ƃv���C���[�̓����蔻��
		hitPolyDim = MV1CollCheck_Sphere((*itr)->GetModelHandle(), FRAME_INDEX, player->GetCollide().worldCenter, player->GetCollide().radius);
		
		VECTOR moveCandidate;													//�v���C���[���S���
		VECTOR newCenter = moveCandidate = player->GetCollide().worldCenter;	//�ړ����

		//�v���C���[���}�b�v�ɓ����������ǂ���
		if (hitPolyDim.HitNum)
		{

			//�Փ˃|���S�������ׂĉ���Ă߂荞�݂�����
			for (int i = 0; i < hitPolyDim.HitNum; ++i)
			{
				//�Փ˃|���S���̕�
				VECTOR edge1 = hitPolyDim.Dim[i].Position[1] - hitPolyDim.Dim[i].Position[0];
				VECTOR edge2 = hitPolyDim.Dim[i].Position[2] - hitPolyDim.Dim[i].Position[0];

				//�Փ˃|���S���̕ӂ��A�|���S���ʂ̖@���x�N�g�������߂�
				planeNormal = VNorm(VCross(edge1, edge2));

				//�v���C���[���S�ɍł��߂��|���S�����ʂ̓_�����߂�
				VECTOR tmp = moveCandidate - hitPolyDim.Dim[i].Position[0];
				float dot = VDot(planeNormal, tmp);

				//�Փ˓_
				VECTOR hitPos = moveCandidate - planeNormal * dot;

				//�v���C���[���ǂꂭ�炢�߂荞��ł��邩���Z�o
				VECTOR tmp2 = moveCandidate - hitPos;
				float len = VSize(tmp2);

				//�߂荞��ł���ꍇ�̓v���C���[�̒��S�������߂�
				if (HitCheck_Sphere_Triangle(moveCandidate, player->GetCollide().radius,
					hitPolyDim.Dim[i].Position[0],
					hitPolyDim.Dim[i].Position[1],
					hitPolyDim.Dim[i].Position[2]))
				{
					//�߂荞�݉�������ʒu�܂ňړ�
					len = player->GetCollide().radius - len;
					moveVec = planeNormal * len;
					moveCandidate += moveVec;
				}

				//�ړ������ړ��ʒu�ɂ���
				newCenter = moveCandidate;

				pushBack = newCenter - player->GetDirection() + VScale(player->GetDirection(), SCALE);

				//�v���C���[�̍��W�ɉ����߂��ʂ�������
				player->HitMap(pushBack);
			}
		}
	}
}

/// <summary>
/// �S�[���I�u�W�F�N�g�ƃv���C���[�̓����蔻��
/// </summary>
/// <param name="goalFlag">�S�[���I�u�W�F�N�g�̃|�C���^</param>
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
}

/// <summary>
/// �G�l�~�[�̎���ɃP�[�L���������ꍇ
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
/// <param name="enemy">�G�l�~�[�̃|�C���^</param>
/// <param name="cakeBullet">�P�[�L�o���b�g�̃|�C���^</param>
void HitChecker::VisualAngleCake(float deltaTime, vector<Enemy*>* enemy, vector<CakeBullet*>* cakeBullet)
{
	for (auto itre = enemy->begin(); itre != enemy->end(); ++itre)
	{
		for (auto itr = cakeBullet->begin(); itr != cakeBullet->end(); ++itr)
		{
			//�o���b�g����G�l�~�[�̍��W���������l���擾
			VECTOR sub = (*itr)->bullet->GetPosition() - (*itre)->GetPosition();

			//�o���b�g�ƃG�l�~�[�̋������v�Z
			float bulletDirection = VSize(sub);

			//�x�N�g���̐��K��
			sub = VNorm(sub);

			//���όv�Z
			float dot = VDot(sub, (*itre)->GetDirection());

			float range = RANGE_DEGREE * PI;

			//�G�l�~�[�̎����cos�ɂ���
			float radian = cosf(range / RANGE_HALF);

			//�x�N�g���ƃG�l�~�[�̒����̔�r
			if (LENGTH > bulletDirection)
			{
				//�o���b�g���G�l�~�[�̎���͈͓��ɂ���Ȃ��
				if (radian <= dot)
				{
					(*itre)->CakeFind(deltaTime, sub);

					if ((*itre)->CakeFlag())
					{
						break;
					}
				}
			}
			else
			{
				(*itre)->CakeReset();
			}
		}
	}
}

/// <summary>
/// �G�l�~�[�̎���Ƀv���C���[���������ꍇ
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <param name="enemy">�G�l�~�[�̃|�C���^</param>
void HitChecker::VisualAnglePlayer(Player* player, vector<Enemy*>* enemy)
{
	for (auto itr = enemy->begin(); itr != enemy->end(); ++itr)
	{
		//�v���C���[����G�l�~�[�̍��W���������l���擾
		VECTOR sub = player->GetPosition() - (*itr)->GetPosition();

		//�v���C���[�ƃG�l�~�[�̋������v�Z
		float playerDirection = VSize(sub);

		//�x�N�g���̐��K��
		sub = VNorm(sub);

		//���όv�Z
		float dot = VDot(sub, (*itr)->GetDirection());

		float range = RANGE_DEGREE * PI;

		//�G�l�~�[�̎����cos�ɂ���
		float radian = cosf(range / RANGE_HALF);

		//�x�N�g���ƃG�l�~�[�̒����̔�r
		if (LENGTH > playerDirection)
		{
			//�v���C���[���G�l�~�[�̎���͈͓��ɂ���Ȃ��
			if (radian <= dot)
			{
				(*itr)->PlayerFind(sub);
			}
		}
		else
		{
			(*itr)->PlayerReset();
		}
	}
}