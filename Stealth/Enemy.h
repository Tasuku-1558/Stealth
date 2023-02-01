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

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//�G�l�~�[�̎���ɃP�[�L���������ꍇ
	void VisualAngleWall(VECTOR wallPos);					//�G�l�~�[�̎���ɕǂ��������ꍇ


	const bool Spotted() { return playerSpotted; }			//�v���C���[�����������ǂ�����Ԃ�
	const bool CakeFlag() { return cakeFlag; }				//�P�[�L�����������ǂ�����Ԃ�
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
	void ReactionDraw();						//���A�N�V�����摜�̕`�揈��
	void Finalize();							//�I������

	std::string InputPath(std::string folderPath, //�摜�ASE�̃p�X�����
						  std::string path);

	EnemyState enemyState;						//�G�l�~�[�̏��

	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	float speedCount;		//�G�l�~�[�X�s�[�h�ω��J�E���g
	bool cakeFindFlag;		//�G�l�~�[���P�[�L�����������ǂ���
	bool cakeEatFlag;		//�G�l�~�[���P�[�L�ɋ߂Â��ĐH�ׂĂ��邩�ǂ���

	//�ÓI�萔
	static const std::string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const std::string SOUND_FOLDER_PATH;	//sound�t�H���_�܂ł̃p�X
	static const std::string PLAYER_FIND_PATH;	//�v���C���[���������摜�̃p�X
	static const std::string MARK_PATH;			//�r�b�N���}�[�N�摜�̃p�X
	static const std::string CAKE_EAT_PATH;		//�P�[�L��H�ׂĂ���摜�̃p�X
	static const std::string SPOTTED_SE_PATH;	//�v���C���[����SE���̃p�X
};