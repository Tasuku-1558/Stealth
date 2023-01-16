#pragma once

#include "ObjectBase.h"


/// <summary>
/// �ǃN���X
/// </summary>
class Wall final : public ObjectBase
{
public:

	 Wall(Object WALL, const VECTOR& pos);
	~Wall();

	void Initialize();
	void Finalize();
	void Draw();

private:

	Wall(const Wall&);					//�R�s�[�R���X�g���N�^

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const VECTOR POSITION;		//���f���̈ʒu

};