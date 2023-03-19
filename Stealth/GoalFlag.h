#pragma once

#include "ObjectBase.h"
#include "Math3D.h"
#include "Collision.h"

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
	void Activate();					//����������
	void Finalize();					//�I������

	VECTOR rotate;						//���f���̉�]

	My3dLib::Sphere collisionSphere;	//�����蔻�苅

	//�萔
	const VECTOR SIZE;				//���f���̔{��
	const float ROTATE_SPEED_Y;		//���f���̉�]�X�s�[�h
	const float  RADIUS;			//�S�[���t���O�̔��a

};