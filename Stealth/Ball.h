#pragma once

#include "ObjectBase.h"

class HitChecker;

/// <summary>
/// �{�[���N���X
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball(VECTOR pos);
	 virtual ~Ball();

	void Initialize();					//����������
	void Activate();					//����������
	void Finalize();					//�I������
	void Update();						//�X�V����
	void BallAlive();					//�{�[�����A�N�e�B�u��
	void Draw();						//�`�揈��

	const bool GetAlive() { return alive; }			//�{�[���������Ă邩����ł邩��Ԃ�
	void IsAlive(HitChecker* hitChecker);			//�{�[���������Ă邩����ł��邩�𔻒�

private:

	Ball(const Ball&);					//�R�s�[�R���X�g���N�^

	bool alive;							//�{�[���������Ă邩����ł��邩


	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��

};