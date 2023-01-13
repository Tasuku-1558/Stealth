#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Camera.h"
#include "Ball.h"

class Enemy;
class Bullet;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player(Object PLAYER);		//�R���X�g���N�^
	~Player();					//�f�X�g���N�^

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Camera* camera, Ball* ball, Enemy* enemy);
	void Draw();

	VECTOR GetBulletPos() { return bulletPosition; }

	//�f�o�b�N�p
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetSpeed() { return SPEED; }


private:
	Player(const Player&);								//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera);			//�ړ�����
	void Shoot(float deltaTime, Ball* ball);			//�e�̔��ˏ���
	void FoundEnemy(Enemy* enemy);						//�G�l�~�[�Ɍ��������ꍇ
	void BulletReuse(float deltaTime, Ball* ball);		//�o���b�g�Ďg�p�J�E���g


	Bullet* bullet;

	float bulletCount;				//�e�̌��ʎ���
	VECTOR bulletPosition;			//�e�̈ʒu
};