#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

class Camera;
class Bullet;
class Boal;
class Enemy;


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
	~Player();		//�f�X�g���N�^

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Camera* camera, Boal* boal, Enemy* enemy);
	void Draw();
	bool Geta() { return a; }

	//�f�o�b�N�p
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetFind() { return foundTimes; }
	int GetSpeed() { return SPEED; }


	enum class Cursor cursor;

private:
	Player(const Player&);							//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera);		//�ړ�����
	void Shoot(float deltaTime, Boal* boal);		//�e�̔��ˏ���
	void FoundEnemy(Enemy* enemy);					//�G�l�~�[�Ɍ�����
	void cUpdate(Boal* boal);

	Bullet* bullet;

	int rightArmHandle;
	VECTOR rightArmPosition;
	int count;
	bool a;

	static const VECTOR RIGHT_ARM_POSITION;
};