#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Camera.h"

using namespace std;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player();
	 virtual ~Player();

	void Initialize();															//����������
	void Activate();															//����������

	void Update(float deltaTime, Camera* camera, 
				VECTOR back, bool mapHit);										//�X�V����

	void FoundEnemy(float deltaTime, bool spotted);								//�G�l�~�[�Ɍ��������ꍇ
	void Draw();																//�`�揈��

	const int GetPlayerCount() { return playerFindCount; }						//�G�l�~�[�Ɍ��������񐔂�Ԃ�


private:
	Player(const Player&);														//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//�ړ�����
	void Finalize();															//�I������
	void AfterImage();															//�v���C���[�̎c������
	void HitMap(VECTOR back, bool mapHit);										//�}�b�v�ɏՓ˂���
	string InputPath(string folderPath,											//�p�X�����
					 string path);

	float initialCount;			//�����ʒu�ɖ߂��J�E���g
	int emptyModel[12];			//�c�����f���i�[�p
	VECTOR pastPosition[12];	//�v���C���[�̉ߋ��̈ʒu

	//�萔
	const string IMAGE_FOLDER_PATH;		//image�t�H���_�܂ł̃p�X
	const string PLAYER_FIND_PATH;		//�G�l�~�[�Ɍ����������̉摜�̃p�X
	const int	 AFTER_IMAGE_NUMBER;	//�v���C���[�̎c������
};