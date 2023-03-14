#pragma once

#include "ObjectBase.h"
#include "Collision.h"

/// <summary>
/// ���΃N���X
/// </summary>
class Stone final : public ObjectBase
{
public:
	Stone(const VECTOR& stonePosition);
	virtual ~Stone();

	void Initialize();					//����������
	void Activate();					//����������
	void Finalize();					//�I������
	void Update(float deltaTime);		//�X�V����
	void StoneAlive();					//���΂��A�N�e�B�u��
	void Draw();						//�`�揈��

	const bool GetAlive() { return alive; }			//���΂������Ă邩����ł邩��Ԃ�
	const float GetCollideRadius() { return collisionSphere.radius; }		//�����蔻�苅�̔��a��Ԃ�

private:

	Stone(const Stone&);		//�R�s�[�R���X�g���N�^

	bool alive;					//���΂������Ă邩����ł��邩

	My3dLib::Sphere collisionSphere;		//�����蔻�苅

	//�萔
	const VECTOR SIZE;      //���f���̔{��
	const VECTOR ROTATE;	//���f���̉�]�l
	const float  RADIUS;	//���΂̔��a
};