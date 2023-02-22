#pragma once

#include "ObjectBase.h"

/// <summary>
/// �ǃN���X
/// </summary>
class Wall final : public ObjectBase
{
public:

	 Wall(VECTOR pos);
	 virtual ~Wall();

	void Initialize();					//����������
	void Finalize();					//�I������
	void Draw();						//�`�揈��

private:

	Wall(const Wall&);					//�R�s�[�R���X�g���N�^

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const VECTOR POSITION;		//���f���̈ʒu

};