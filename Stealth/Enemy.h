#pragma once

#include <string>

#include "EnemyBase.h"
#include "Math3D.h"
#include "Collision.h"

class Player;
class Bullet;

using namespace std;

/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy final : public EnemyBase
{
public:
	Enemy(int number, float enemySpeed);
	virtual ~Enemy();

	void Update(float deltaTime, Player* player);		//�X�V����
	void Draw();										//�`�揈��

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//�G�l�~�[�̎���ɃP�[�L���������ꍇ
	void HitPlayer();										//�v���C���[�ƏՓ˂���

	const float GetCollideRadius() { return collisionSphere.radius; }		//�����蔻�苅�̔��a��Ԃ�
	const bool Spotted() { return playerSpotted; }			//�v���C���[�����������ǂ�����Ԃ�
	const bool CakeFlag() { return cakeFlag; }				//�P�[�L�����������ǂ�����Ԃ�
	const bool CakeEatFlag() { return cakeEat; }

private:
	Enemy(const Enemy&);						//�R�s�[�R���X�g���N�^

	void Initialize();							//����������
	void Finalize();							//�I������
	void Move(float deltaTime);					//�ړ�����
	void Position(vector<VECTOR>& id);			//�G�l�~�[�ʒu�ݒ�
	void StateUpdate(float deltaTime);			//�G�l�~�[�̏�ԕω�
	void SetTargetPosition();					//�ړI�n�܂ňړ�����
	void VisualAnglePlayer(Player* player);		//�G�l�~�[�̎���Ƀv���C���[���������ꍇ
	void Reaction();							//�G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
	void CakeEatCount(float deltaTime);			//�b���ɂ���ăP�[�L�̏�ԕω�
	void ReactionDraw();						//���A�N�V�����摜�̕`�揈��
	void EnemyRotate(float deltaTime);			//�G�l�~�[�̉�]����
	bool IsGoal(float deltaTime);				//�ړI�n�ɓ��B�����Ȃ��

	string InputPath(string folderPath,			//�摜�̃p�X�����
					 string imagePath);

	//�G�l�~�[�̓���
	enum class EnemyState
	{
		CRAWL,			//����
		ARRIVAL,		//�ړI�n�ɓ���
		ROTATION,		//�����]��
	};

	//�I�u�W�F�N�g���Ƃ̃G�l�~�[�̔���
	enum class EnemyReaction
	{
		NORMAL,			//�����Ă��Ȃ�
		PLAYER,			//�v���C���[
		CAKE,			//�P�[�L
	};

	EnemyState enemyState;						//�G�l�~�[�̓���
	EnemyReaction enemyReaction;				//�I�u�W�F�N�g���Ƃ̃G�l�~�[�̔���

	My3dLib::Sphere collisionSphere;			//�����蔻�苅

	vector<VECTOR>::iterator itr;
	vector<VECTOR> pointList;

	float cakeCount;		//�G�l�~�[�̃P�[�L�̔����J�E���g
	bool cakeFindFlag;		//�G�l�~�[���P�[�L�����������ǂ���

	VECTOR nextDirection;	//��]����������
	bool rotateFlag;		//��]�����邩�����Ȃ���
	float frame;
	bool cakeEat;

	//�萔
	const string IMAGE_FOLDER_PATH;	//Image�t�H���_�܂ł̃p�X
	const string MARK_PATH;			//�r�b�N���}�[�N�摜�̃p�X
};