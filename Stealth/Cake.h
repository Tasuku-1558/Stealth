#pragma once

#include "ObjectBase.h"

class HitChecker;

/// <summary>
/// �P�[�L�N���X
/// </summary>
class Cake final : public ObjectBase
{
public:
	 Cake(VECTOR pos);
	 virtual ~Cake();

	void Initialize();					//����������
	void Activate();					//����������
	void Finalize();					//�I������
	void Update();						//�X�V����
	void CakeAlive();					//�P�[�L���A�N�e�B�u��
	void Draw();						//�`�揈��

	const bool GetAlive() { return alive; }			//�P�[�L�������Ă邩����ł邩��Ԃ�
	void IsAlive(HitChecker* hitChecker);			//�P�[�L�������Ă邩����ł��邩�𔻒�

private:

	Cake(const Cake&);					//�R�s�[�R���X�g���N�^

	bool alive;							//�P�[�L�������Ă邩����ł��邩


	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��

};