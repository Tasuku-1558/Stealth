#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

//�v���C���[���
enum class PlayerState
{
	Nomal,
	Damage,
};

// �v���C���[�N���X
class Player final : public PlayerBase
{
public:
	 Player();		//�R���X�g���N�^
	~Player();		//�f�X�g���N�^

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetHP() { return hp; }

	enum class PlayerState playerState;

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	void Move(float deltaTime);		//�ړ�����
	void pUpdate();


	int rightArmHandle;
	VECTOR rightArmPosition;


	static const VECTOR RIGHT_ARM_POSITION;
};