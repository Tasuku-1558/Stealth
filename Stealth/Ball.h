#pragma once

#include "ObjectBase.h"
#include "HitChecker.h"


/// <summary>
/// �{�[���N���X
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball(VECTOR pos);
	~Ball();

	void Initialize();
	void Finalize();
	void Update(HitChecker* hitChecker);
	void SetDead();							//�{�[�����A�N�e�B�u��
	void Draw();

	bool GetAlive() { return alive; }

private:

	Ball(const Ball&);								//�R�s�[�R���X�g���N�^
	void IsAlive(HitChecker* hitChecker);			//�����Ă邩����ł��邩

	bool alive;										//�{�[���������Ă邩����ł��邩

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const VECTOR POSITION;		//���f���̈ʒu
};