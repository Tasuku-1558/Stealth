#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

class Camera;
class Bullet;
class Ball;
class Enemy;
class HitChecker;

/// <summary>
/// �J�[�\���̏��
/// </summary>
enum class Cursor
{
	SELECTION,
	PUSH,
};

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
	void Update(float deltaTime, Camera* camera, Ball* ball, Enemy* enemy, HitChecker* hitChecker);
	void Draw();


	//�f�o�b�N�p
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetSpeed() { return SPEED; }


	enum class Cursor cursor;

private:
	Player(const Player&);							//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera);		//�ړ�����
	void Shoot(float deltaTime, Ball* ball);		//�e�̔��ˏ���
	void FoundEnemy(Enemy* enemy);					//�G�l�~�[�Ɍ��������ꍇ
	void aa(HitChecker* hitChecker);
	void cUpdate(Ball* ball);

	Bullet* bullet;

	int rightArmHandle;
	VECTOR rightArmPosition;

	static const VECTOR RIGHT_ARM_POSITION;
};