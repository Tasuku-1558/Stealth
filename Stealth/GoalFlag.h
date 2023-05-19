#pragma once

#include <string>
#include "ObjectBase.h"
#include "Math3D.h"
#include "Collision.h"

using namespace std;

/// <summary>
/// �S�[���I�u�W�F�N�g�N���X
/// </summary>
class GoalFlag final : public ObjectBase
{
public:
	GoalFlag(VECTOR goalPosition);
	virtual ~GoalFlag();

	void Update(float deltaTime);		//�X�V����
	void Draw();						//�`�揈��

	const float GetCollideRadius() { return collisionSphere.radius; }		//�����蔻�苅�̔��a��Ԃ�

private:
	GoalFlag(const GoalFlag&);			//�R�s�[�R���X�g���N�^

	void Initialize();					//����������
	void Finalize();					//�I������

	int goalImage;						//�S�[�������̉摜
	VECTOR rotate;						//���f���̉�]
	My3dLib::Sphere collisionSphere;	//�����蔻�苅

	//�萔
	const float  ROTATE_SPEED;			//���f���̉�]�X�s�[�h
	const float  RADIUS;				//�S�[���t���O�̔��a
	const float  GOAL_CENTER_POSITION;	//�S�[�������̒��S���W
	const float  GOAL_SIZE;				//�S�[�������̑傫��
	const float  GOAL_ANGLE;			//�S�[�������̉�]�l
	const VECTOR SIZE;					//���f���̔{��
	const string IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string GOAL_PATH;				//�S�[�������̉摜�̃p�X
};