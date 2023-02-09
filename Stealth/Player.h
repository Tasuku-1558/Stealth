#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Camera.h"


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


	//�f�o�b�N�p
	float GetSpeed() { return SPEED; }


private:
	Player(const Player&);														//�R�s�[�R���X�g���N�^

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//�ړ�����
	void Finalize();															//�I������
	void AfterImage(float deltaTime);											//�v���C���[�̎c��

	float initialCount;			//�����ʒu�ɖ߂��J�E���g
	int emptyModel[3];
	VECTOR pastPosition[3];
	float count;

	//�ÓI�萔
	static const std::string SOUND_FOLDER_PATH;		//sound�t�H���_�܂ł̃p�X
	static const std::string SPOTTED_SE_PATH;		//�G�l�~�[�Ɍ�����������SE���̃p�X
	static const int		 AFTER_IMAGE_NUMBER;	//�v���C���[�̎c������
};