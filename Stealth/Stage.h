#pragma once

#include "ObjectBase.h"

/// <summary>
/// �X�e�[�W�u���b�N�N���X
/// </summary>
class Stage final : public ObjectBase
{
public:
	Stage(VECTOR position);
	virtual ~Stage();

	void Draw();			//�`�揈��

private:
	Stage(const Stage&);	//�R�s�[�R���X�g���N�^

};