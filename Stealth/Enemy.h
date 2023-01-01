#pragma once

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"
#include <vector>

class Map;
class Player;

/// <summary>
/// �G�l�~�[�̏��
/// </summary>
enum class EnemyState
{
	CRAWL,			//����
	ARRIVAL,		//�ړI�n�ɓ���
};


/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(Map* map);		//�R���X�g���N�^
	~Enemy();				//�f�X�g���N�^

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void Draw();
	bool Discovery() { return discovery; }

	//�f�o�b�N�p
	int GetPlayerCount() { return playerCount; }

	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);						//�R�s�[�R���X�g���N�^

	void Position(Map* map);					//�G�l�~�[�ʒu�ݒ�
	bool IsGoal(float deltaTime);				//�ړI�n�ɓ��B�����Ȃ��
	void eUpdate(float deltaTime);				//��ԕω�
	void SetTargetPosition();					//�ړ�����
	void VisualAngle(Player* player);			//����p�̌v�Z
	void Reaction(Object object);				//�G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
	void Finalize();


	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	VECTOR targetPosition;			//�ړI�n�̍��W
	Object object;					//�I�u�W�F�N�g�̃^�O

	const float length;				//����p�̋���
	bool discovery;					//����

	int playerCount;				//�v���C���[����������

};