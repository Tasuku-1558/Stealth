#pragma once

#include "ObjectBase.h"

class HitChecker;

/// <summary>
/// �{�[���N���X
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball();
	~Ball();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(HitChecker* hitChecker);
	void Draw();

	bool GetAlive() { return alive; }

private:

	void IsAlive(HitChecker* hitChecker);			//�����Ă邩����ł��邩

	bool alive;										//�{�[���������Ă邩����ł��邩

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const VECTOR POSITION;		//���f���̈ʒu
};