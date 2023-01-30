#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Camera.h"

class Enemy;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player();
	 virtual ~Player();

	void Initialize();															//����������
	void Finalize();															//�I������
	void Activate();															//����������
	void Update(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//�X�V����
	void FoundEnemy(Enemy* enemy);												//�G�l�~�[�Ɍ��������ꍇ
	void Draw();																//�`�揈��


	//�f�o�b�N�p
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetSpeed() { return SPEED; }


private:
	Player(const Player&);														//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//�ړ�����
	int count;
};