#pragma once

#include "PlayerBase.h"
#include "Math3D.h"
#include "Collision.h"
#include "EffectManager.h"


/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final : public PlayerBase
{
public:
	Player(EffectManager* const inEffect);
	virtual ~Player();

	void Update(float deltaTime);						//�X�V����
	void Draw();										//�`�揈��

	void FoundEnemy(float deltaTime, bool spotted);		//�G�l�~�[�Ɍ��������ꍇ
	void HitMap(VECTOR pushBack);						//�}�b�v�ɏՓ˂���

	const int FindCount() { return playerFindCount; }				//�G�l�~�[�Ɍ��������񐔂�Ԃ�
	const My3dLib::Sphere GetCollide() { return collisionSphere; }	//�����蔻�苅��Ԃ�

private:
	Player(const Player&);			//�R�s�[�R���X�g���N�^

	void Initialize();				//����������
	void Move(float deltaTime);		//�ړ�����
	void Finalize();				//�I������
	void KeyInput();				//�L�[���͏���
	void AfterImage();				//�v���C���[�̎c������
	void FoundCount();				//�G�l�~�[�Ɍ����������̏����ʒu�֖߂��J�E���g

	//�L�[����
	struct Key
	{
		int input;	//�L�[�̎��
		VECTOR dir;	//����
	};

	EffectManager* effectManager;		//�G�t�F�N�g�}�l�[�W���[�̃|�C���^

	My3dLib::Sphere collisionSphere;	//�����蔻�苅
};