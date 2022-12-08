#pragma once

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Field;

//�G�l�~�[�̏��
enum class EnemyState
{
	Nomal,
	Attack,
};

//�G�l�~�[�N���X
class Enemy final : public EnemyBase
{
public:
	 Enemy();		//�R���X�g���N�^
	~Enemy();		//�f�X�g���N�^

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime,Field* field);
	void Draw();

	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);		//�R�s�[�R���X�g���N�^

	void eUpdate();						//��ԕω�
	void GoBuck(float deltaTime,Field* field);		//�G�l�~�[�e�s���p�^�[��

	
};