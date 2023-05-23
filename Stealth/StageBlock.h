#pragma once

#include "ObjectBase.h"

/// <summary>
/// �X�e�[�W�u���b�N�N���X
/// </summary>
class StageBlock final : public ObjectBase
{
public:
	StageBlock(VECTOR position, VECTOR scale);
	virtual ~StageBlock();

	void Update(float deltaTime);	//�X�V����
	void Draw();					//�`�揈��

private:
	StageBlock(const StageBlock&);	//�R�s�[�R���X�g���N�^
};