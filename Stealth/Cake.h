#pragma once

#include "ObjectBase.h"
#include "Collision.h"

/// <summary>
/// �P�[�L�N���X
/// </summary>
class Cake final : public ObjectBase
{
public:
	Cake(const VECTOR& cakePosition);
	virtual ~Cake();

	void Update(float deltaTime);		//�X�V����
	void Draw();						//�`�揈��

	void CakeAlive();					//�P�[�L���A�N�e�B�u��
	void HitCake();						//�P�[�L�ɏՓ˂���

	const bool GetAlive() { return alive; }									//�P�[�L�������Ă邩����ł邩��Ԃ�
	const float GetCollideRadius() { return collisionSphere.radius; }		//�����蔻�苅�̔��a��Ԃ�

private:
	Cake(const Cake&);			//�R�s�[�R���X�g���N�^

	void Initialize();			//����������
	void Finalize();			//�I������

	bool alive;					//�P�[�L�������Ă邩����ł��邩

	My3dLib::Sphere collisionSphere;	//�����蔻�苅

	//�萔
	const float  RADIUS;		//�P�[�L�̔��a
	const VECTOR SIZE;          //���f���̔{��
	const VECTOR ROTATE;		//���f���̉�]�l

};