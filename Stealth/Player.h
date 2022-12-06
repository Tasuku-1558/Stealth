#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"


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

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	void Move(float deltaTime);		//�ړ�����

	int rightArmHandle;
	VECTOR rightArmPosition;
	static const VECTOR RIGHT_ARM_POSITION;
};