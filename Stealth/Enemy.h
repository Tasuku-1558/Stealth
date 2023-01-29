#pragma once

#include <string>
#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;

/// <summary>
/// �G�l�~�[�N���X(�ԐF)
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(std::vector<VECTOR>& id);
	 virtual ~Enemy();

	void Initialize();									//����������
	void Activate();									//����������
	void Update(float deltaTime, Player* player);		//�X�V����
	void Draw();										//�`�揈��

	void VisualAngleBall(Bullet* bullet);				//�G�l�~�[�̎���Ƀ{�[�����������ꍇ
	void VisualAngleWall(VECTOR wallPos);				//�G�l�~�[�̎���ɕǂ��������ꍇ

	const bool Spotted() { return playerSpotted; }			//�v���C���[�����������ǂ�����Ԃ�
	const bool BallFlag() { return ballFlag; }				//�{�[�������������ǂ�����Ԃ�
	const int GetPlayerCount() { return playerFindCount; }	//�v���C���[���������񐔂�Ԃ�
	
	//�G�l�~�[�̏��
	enum class EnemyState
	{
		CRAWL,			//����
		ARRIVAL,		//�ړI�n�ɓ���
	};

private:
	Enemy(const Enemy&);						//�R�s�[�R���X�g���N�^

	void Position(std::vector<VECTOR>& id);		//�G�l�~�[�ʒu�ݒ�
	bool IsGoal(float deltaTime);				//�ړI�n�ɓ��B�����Ȃ��
	void eUpdate(float deltaTime);				//�G�l�~�[�̏�ԕω�
	void SetTargetPosition();					//�ړI�n�܂ňړ�����
	void VisualAnglePlayer(Player* player);		//�G�l�~�[�̎���Ƀv���C���[���������ꍇ
	
	void Reaction();							//�G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
	void Finalize();							//�I������

	EnemyState enemyState;						//�G�l�~�[�̏��

	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	int count;
	//�ÓI�萔
	static const std::string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const std::string SOUND_FOLDER_PATH;	//sound�t�H���_�܂ł̃p�X
	static const std::string FIND_PATH;			//���������摜�̃p�X
	static const std::string MARK_PATH;			//�r�b�N���}�[�N�摜�̃p�X
	static const std::string SPOTTED_SE_PATH;	//�v���C���[����SE���̃p�X
};