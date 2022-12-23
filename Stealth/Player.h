#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

class Camera;
class Bullet;
class Boal;

/// <summary>
/// �v���C���[���
/// </summary>
enum class PlayerState
{
	Nomal,
};

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player();		//�R���X�g���N�^
	~Player();		//�f�X�g���N�^

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Camera* camera, Boal* boal);
	void Draw();

	/*VECTOR GetUp() { return UP; }
	VECTOR GetDown() { return DOWN; }
	VECTOR GetLeft() { return LEFT; }
	VECTOR GetRight() { return RIGHT; }*/

	//�f�o�b�N�p
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetFind() { return foundTimes; }
	int GetSpeed() { return SPEED; }


	enum class PlayerState playerState;

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera);		//�ړ�����
	void Shoot(float deltaTime, Boal* boal);							//�e�̔��ˏ���
	void pUpdate();

	Bullet* bullet;

	int rightArmHandle;
	VECTOR rightArmPosition;
	bool boalGet;


	static const VECTOR RIGHT_ARM_POSITION;
};