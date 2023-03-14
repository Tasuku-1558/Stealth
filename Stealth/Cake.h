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

	void Initialize();					//����������
	void Activate();					//����������
	void Finalize();					//�I������
	void Update(float deltaTime);		//�X�V����
	void CakeAlive();					//�P�[�L���A�N�e�B�u��
	void Draw();						//�`�揈��
	void HitCake();						//�P�[�L�ɏՓ˂���

	const bool GetAlive() { return alive; }									//�P�[�L�������Ă邩����ł邩��Ԃ�
	const float GetCollideRadius() { return collisionSphere.radius; }		//�����蔻�苅�̔��a��Ԃ�

private:

	Cake(const Cake&);			//�R�s�[�R���X�g���N�^

	bool alive;					//�P�[�L�������Ă邩����ł��邩

	My3dLib::Sphere collisionSphere;	//�����蔻�苅

	//�萔
	const VECTOR SIZE;          //���f���̔{��
	const VECTOR ROTATE;		//���f���̉�]�l
	const float  RADIUS;		//�P�[�L�̔��a

};