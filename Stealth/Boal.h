#pragma once

#include "ObjectBase.h"

class HitChecker;

/// <summary>
/// �{�[���N���X
/// </summary>
class Boal final : public ObjectBase
{
public:
	 Boal();
	~Boal();

	void Initialize();
	void Finalize();
	void Activate();
	void Update();
	void Draw();

	bool IsAlive(HitChecker* hitChecker);			//�����Ă邩����ł��邩

private:

	bool alive;			//�{�[���������Ă邩����ł��邩

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const VECTOR POSITION;		//���f���̈ʒu
};