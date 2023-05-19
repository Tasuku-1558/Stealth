#pragma once

#include "EnemyBase.h"
#include "Math3D.h"
#include "Collision.h"

/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy final : public EnemyBase
{
public:
	Enemy(int movePattern, float enemySpeed);
	virtual ~Enemy();

	void Update(float deltaTime, VECTOR playerPosition);	//�X�V����
	void Draw();											//�`�揈��

	void VisualAngleCake(float deltaTime, VECTOR bulletPosition);	//�G�l�~�[�̎���ɃP�[�L���������ꍇ
	void Reaction();								//�G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
	void HitPlayer();												//�v���C���[�ƏՓ˂���

	const float GetCollideRadius() { return collisionSphere.radius; }	//�����蔻�苅�̔��a��Ԃ�
	const bool Spotted() { return playerSpotted; }						//�v���C���[�����������ǂ�����Ԃ�
	const bool CakeFlag() { return cakeFlag; }							//�P�[�L�����������ǂ�����Ԃ�

	//�I�u�W�F�N�g���Ƃ̃G�l�~�[�̔���
	enum class EnemyReaction
	{
		NORMAL,		//�����Ă��Ȃ�
		PLAYER,		//�v���C���[
		CAKE,		//�P�[�L
	};

	EnemyReaction enemyReaction;		//�I�u�W�F�N�g���Ƃ̃G�l�~�[�̔���

private:
	Enemy(const Enemy&);							//�R�s�[�R���X�g���N�^

	void Initialize();								//����������
	void Finalize();								//�I������
	void Move(float deltaTime);						//�ړ�����
	void Position(vector<VECTOR>& id);				//�G�l�~�[�ʒu�ݒ�
	void StateUpdate(float deltaTime);				//�G�l�~�[�̏�Ԃ̕ω�
	void SetTargetPosition();						//�ړI�n�܂ňړ�����
	void VisualAnglePlayer(VECTOR playerPosition);	//�G�l�~�[�̎���Ƀv���C���[���������ꍇ
	void CakeEatCount(float deltaTime);				//�b���ɂ���ăP�[�L�̏�ԕω�
	void ReactionDraw();							//���A�N�V�����摜�̕`�揈��
	void EnemyRotate(float deltaTime);				//�G�l�~�[�̉�]����
	void EnemyRotateTime(float deltaTime);			//�G�l�~�[�̉�]�̎���
	bool IsGoal(float deltaTime);					//�ړI�n�ɓ��B�����Ȃ��

	//�G�l�~�[�̓���
	enum class EnemyState
	{
		CRAWL,		//����
		ARRIVAL,	//�ړI�n�ɓ���
		ROTATION,	//�����]��
	};

	struct RotateTime
	{
		EnemyReaction enemyReaction;	//�I�u�W�F�N�g���Ƃ̃G�l�~�[�̔���
		float time;						//�e�I�u�W�F�N�g�̉�]����
	};

	EnemyState enemyState;				//�G�l�~�[�̓���

	My3dLib::Sphere collisionSphere;	//�����蔻�苅

	vector<VECTOR>::iterator itr;		//���W���X�g�̃C�e���[�^
	vector<VECTOR> positionList;		//�G�l�~�[�̍��W���X�g

	float cakeCount;		//�G�l�~�[�̃P�[�L�̔����J�E���g
	bool cakeFindFlag;		//�G�l�~�[���P�[�L�����������ǂ���
	bool rotateFlag;		//��]�����邩�����Ȃ���
	VECTOR nextDirection;	//��]����������
};