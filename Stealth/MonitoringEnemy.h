#pragma once

#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;


/// <summary>
/// �Ď��G�l�~�[�N���X
/// </summary>
class MonitoringEnemy final : public EnemyBase
{
public:
	MonitoringEnemy(std::vector<VECTOR>& id);
	virtual ~MonitoringEnemy();

	void Initialize();									//����������
	void Activate();									//����������
	void Update(float deltaTime);						//�X�V����
	void Draw();										//�`�揈��

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//�G�l�~�[�̎���ɃP�[�L���������ꍇ
	void VisualAngleWall(VECTOR wallPos);					//�G�l�~�[�̎���ɕǂ��������ꍇ


	const bool Spotted() { return playerSpotted; }			//�v���C���[�����������ǂ�����Ԃ�
	const int GetPlayerCount() { return playerFindCount; }	//�v���C���[���������񐔂�Ԃ�

	//�G�l�~�[�̏��
	enum class EnemyState
	{
		CRAWL,			//����
		ARRIVAL,		//�ړI�n�ɓ���
	};

private:
	MonitoringEnemy(const MonitoringEnemy&);				//�R�s�[�R���X�g���N�^


	EnemyState enemyState;						//�G�l�~�[�̏��


};