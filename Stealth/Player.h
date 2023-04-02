#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Collision.h"
#include "EffectManager.h"
#include "HitChecker.h"


using namespace std;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final : public PlayerBase
{
public:
	Player(EffectManager* const inEffect, HitChecker* const inHitChecker);
	virtual ~Player();

	void Update(float deltaTime);									//�X�V����

	void FoundEnemy(float deltaTime, bool spotted);					//�G�l�~�[�Ɍ��������ꍇ
	void Draw();													//�`�揈��

	const int FindCount() { return playerFindCount; }				//�G�l�~�[�Ɍ��������񐔂�Ԃ�
	const My3dLib::Sphere GetCollide() { return collisionSphere; }	//�����蔻�苅��Ԃ�

private:
	Player(const Player&);					//�R�s�[�R���X�g���N�^

	void Initialize();						//����������
	void Move(float deltaTime);				//�ړ�����
	void Finalize();						//�I������
	void KeyInput();						//�L�[���͏���
	void AfterImage();						//�v���C���[�̎c������
	void FoundCount();						//�G�l�~�[�Ɍ����������̏����ʒu�֖߂��J�E���g
	void HitMap();							//�}�b�v�ɏՓ˂���
	string InputPath(string folderPath,		//�p�X�����
					 string path);

	EffectManager* effectManager;	//�G�t�F�N�g�}�l�[�W���[�̃|�C���^
	HitChecker* hitChecker;			//�q�b�g�`�F�b�J�[�̃|�C���^


	float initialCount;				//�����ʒu�ɖ߂��J�E���g
	int afterImageModel[12];		//�c�����f���i�[�p
	VECTOR pastPosition[12];		//�v���C���[�̉ߋ��̈ʒu

	My3dLib::Sphere collisionSphere;	//�����蔻�苅

	//�萔
	const string IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string PLAYER_FIND_PATH;		//�G�l�~�[�Ɍ����������̉摜�̃p�X
	const int	 AFTER_IMAGE_NUMBER;	//�v���C���[�̎c������
};