#pragma once

#include "ObjectBase.h"

/// <summary>
/// �{�[���N���X
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball(VECTOR pos);
	 virtual ~Ball();

	void Initialize();
	void Activate();
	void Finalize();
	void Update();
	void SetAlive();							//�{�[�����A�N�e�B�u��
	void Draw();

	bool GetAlive() { return alive; }
	void IsAlive(bool hit);			//�����Ă邩����ł��邩

private:

	Ball(const Ball&);								//�R�s�[�R���X�g���N�^

	bool alive;										//�{�[���������Ă邩����ł��邩

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
};