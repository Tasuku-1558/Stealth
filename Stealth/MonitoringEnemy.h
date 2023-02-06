#pragma once

#include <vector>
#include <string>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;


/// <summary>
/// �Ď��G�l�~�[�N���X
/// </summary>
class MonitoringEnemy final : public EnemyBase
{
public:
	MonitoringEnemy(std::vector<VECTOR>& id);
	virtual ~MonitoringEnemy();

	void Initialize();									//����������
	void Activate();									//����������
	void Update(float deltaTime, Player* player);		//�X�V����
	void Draw();										//�`�揈��

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//�G�l�~�[�̎���ɃP�[�L���������ꍇ
	void VisualAngleWall(VECTOR wallPos);					//�G�l�~�[�̎���ɕǂ��������ꍇ

	const bool Spotted() { return playerSpotted; }			//�v���C���[�����������ǂ�����Ԃ�

	//�G�l�~�[�̏��
	enum class EnemyState
	{
		CRAWL,			//����
		ARRIVAL,		//�ړI�n�ɓ���
	};

private:
	MonitoringEnemy(const MonitoringEnemy&);						//�R�s�[�R���X�g���N�^

	void Position(std::vector<VECTOR>& id);		//�G�l�~�[�ʒu�ݒ�
	bool IsGoal(float deltaTime);				//�ړI�n�ɓ��B�����Ȃ��
	void eUpdate(float deltaTime);				//�G�l�~�[�̏�ԕω�
	void SetTargetPosition();					//�ړI�n�܂ňړ�����
	void VisualAnglePlayer(Player* player);		//�G�l�~�[�̎���Ƀv���C���[���������ꍇ

	void Reaction();							//�G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
	void CakeEatCount(float deltaTime);			//�b���ɂ���ăP�[�L�̏�ԕω�
	void ReactionDraw();						//���A�N�V�����摜�̕`�揈��
	void Finalize();							//�I������

	std::string InputPath(std::string folderPath, //�摜�̃p�X�����
		std::string imagePath);

	EnemyState enemyState;						//�G�l�~�[�̏��

	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	float cakeCount;		//�G�l�~�[�̃P�[�L�̔����J�E���g
	bool cakeFindFlag;		//�G�l�~�[���P�[�L�����������ǂ���
	bool cakeEatFlag;		//�G�l�~�[���P�[�L�ɋ߂Â��ĐH�ׂĂ��邩�ǂ���
	bool cakeHalfFlag;		//�P�[�L�������ɂȂ��Ă��邩�ǂ���

	VECTOR a;

	//�ÓI�萔
	static const std::string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const std::string PLAYER_FIND_PATH;	//�v���C���[���������摜�̃p�X
	static const std::string MARK_PATH;			//�r�b�N���}�[�N�摜�̃p�X
	static const std::string CAKE_PATH;			//�P�[�L�摜�̃p�X
	static const std::string CAKE_HALF_PATH;	//�P�[�L�������̉摜�̃p�X


};