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
	 Player();				//�R���X�g���N�^
	 virtual ~Player();		//�f�X�g���N�^

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Camera* camera, VECTOR back, bool mapHit);
	void EnemyUpdate(Enemy* enemy);
	void Draw();


	//�f�o�b�N�p
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetSpeed() { return SPEED; }
	VECTOR Prev() { return previewPosition; }


private:
	Player(const Player&);								//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);			//�ړ�����
	void FoundEnemy(Enemy* enemy);						//�G�l�~�[�Ɍ��������ꍇ


	VECTOR previewPosition;
};