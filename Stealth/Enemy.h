#pragma once

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"
#include <vector>

class Map;

/// <summary>
/// �G�l�~�[�̏��
/// </summary>
enum class EnemyState
{
	Crawl,			//����
	Arrival,		//�ړI�n�ɓ���
	Discovery,		//�v���C���[����
};


/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy();		//�R���X�g���N�^
	~Enemy();		//�f�X�g���N�^

	void Initialize(Map* map);
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);		//�R�s�[�R���X�g���N�^

	void Position(Map* map);
	void eUpdate();								//��ԕω�
	void ActionPattern(float deltaTime);		//�G�l�~�[�e�s���p�^�[��

	
	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;
	
};