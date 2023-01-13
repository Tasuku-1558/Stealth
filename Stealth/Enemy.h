#pragma once

#include <string>
#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"
#include "Map.h"
#include "SecondStageMap.h"
#include "Player.h"


/// <summary>
/// �G�l�~�[�̏��
/// </summary>
enum class EnemyState
{
	CRAWL,			//����
	ARRIVAL,		//�ړI�n�ɓ���
};


/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(Map* map);		//�R���X�g���N�^
	 Enemy(SecondStageMap* secondStageMap);
	~Enemy();				//�f�X�g���N�^

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void Draw();

	bool Discovery() { return discovery; }

	int GetPlayerCount() { return playerFindCount; }
	
	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);						//�R�s�[�R���X�g���N�^

	void Position(Map* map);					//�G�l�~�[�ʒu�ݒ�
	void FirstPosition(SecondStageMap* secondStageMap);
	void SecondPosition(SecondStageMap* secondStageMap);
	bool IsGoal(float deltaTime);				//�ړI�n�ɓ��B�����Ȃ��
	void eUpdate(float deltaTime);				//��ԕω�
	void SetTargetPosition();					//�ړ�����
	void VisualAngle(Player* player);			//����p�̌v�Z
	void VisualAngleBall(Player* player);			//����p�̌v�Z
	void Reaction(Object object);				//�G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
	void Finalize();


	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	

	//�ÓI�萔
	static const std::string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const std::string SOUND_FOLDER_PATH;	//sound�t�H���_�܂ł̃p�X
	static const std::string FIND_PATH;			//���������摜�̃p�X
	static const std::string VIEW_RANGE_PATH;
	static const std::string MARK_PATH;			//�r�b�N���}�[�N�摜�̃p�X
	static const std::string DISCOVERY_SE_PATH;	//�v���C���[����SE���̃p�X
};