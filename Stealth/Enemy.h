#pragma once

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"


/// <summary>
/// �G�l�~�[�̏��
/// </summary>
enum class EnemyState
{
	Crawl,			//���񃂁[�h
	Tracking,		//�ǔ����[�h
};

/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy();		//�R���X�g���N�^
	~Enemy();		//�f�X�g���N�^

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);		//�R�s�[�R���X�g���N�^

	void eUpdate();						//��ԕω�
	void GoBuck(float deltaTime);		//�G�l�~�[�e�s���p�^�[��

	
};