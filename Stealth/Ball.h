#pragma once

#include "ObjectBase.h"

/// <summary>
/// �{�[���N���X
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball(const VECTOR& pos);
	~Ball();

	void Initialize();
	void Finalize();
	void Update(bool hit);
	void SetDead();							//�{�[�����A�N�e�B�u��
	void Draw();

	bool GetAlive() { return alive; }

private:

	Ball(const Ball&);								//�R�s�[�R���X�g���N�^
	void IsAlive(bool hit);			//�����Ă邩����ł��邩

	bool alive;										//�{�[���������Ă邩����ł��邩

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const VECTOR POSITION;		//���f���̈ʒu
};