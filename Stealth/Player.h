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

	void Update(float deltaTime, Camera* camera, 
				VECTOR back, bool mapHit);										//�X�V����

	void FoundEnemy(float deltaTime, Enemy* enemy);								//�G�l�~�[�Ɍ��������ꍇ
	void Draw();																//�`�揈��

	const int GetPlayerCount() { return playerFindCount; }						//�G�l�~�[�Ɍ��������񐔂�Ԃ�


	//�f�o�b�N�p
	float GetSpeed() { return SPEED; }


private:
	Player(const Player&);														//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//�ړ�����

	float initialCount;		//�����ʒu�ɖ߂��J�E���g
	int emptyModel;
	VECTOR pastPosition;
	float count;

	//�ÓI�萔
	static const std::string SOUND_FOLDER_PATH;		//sound�t�H���_�܂ł̃p�X
	static const std::string SPOTTED_SE_PATH;		//�G�l�~�[�Ɍ�����������SE���̃p�X

};