#pragma once

#include <string>
#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;

/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(std::vector<VECTOR>& id);		//�R���X�g���N�^
	 virtual ~Enemy();								//�f�X�g���N�^

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void Draw();

	void VisualAngleBall(VECTOR bulletPos);			//����p�̌v�Z
	void VisualAngleWall(VECTOR wallPos);

	bool Discovery() { return discovery; }
	int GetPlayerCount() { return playerFindCount; }
	
	//�G�l�~�[�̏��
	enum class EnemyState
	{
		CRAWL,			//����
		ARRIVAL,		//�ړI�n�ɓ���
	};

private:
	Enemy(const Enemy&);						//�R�s�[�R���X�g���N�^

	void Position(std::vector<VECTOR>& num);	//�G�l�~�[�ʒu�ݒ�
	bool IsGoal(float deltaTime);				//�ړI�n�ɓ��B�����Ȃ��
	void eUpdate(float deltaTime);				//��ԕω�
	void SetTargetPosition();					//�ړI�n�܂ňړ�����
	void VisualAngle(Player* player);			//����p�̌v�Z
	
	
	void Reaction();				//�G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
	void Finalize();

	EnemyState enemyState;

	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	int visualModelHandle;
	VECTOR visualPosition;
	VECTOR visualDir;

	//�ÓI�萔
	static const std::string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const std::string SOUND_FOLDER_PATH;	//sound�t�H���_�܂ł̃p�X
	static const std::string FIND_PATH;			//���������摜�̃p�X
	static const std::string MARK_PATH;			//�r�b�N���}�[�N�摜�̃p�X
	static const std::string DISCOVERY_SE_PATH;	//�v���C���[����SE���̃p�X
};