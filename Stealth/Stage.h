#pragma once

#include "ObjectBase.h"

/// <summary>
/// �X�e�[�W�N���X
/// </summary>
class Stage final : public ObjectBase
{
public:
	Stage(/*ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, */VECTOR position);
	virtual ~Stage();

	void Draw();    //�`�揈��

private:
	Stage(const Stage&);	//�R�s�[�R���X�g���N�^

	int stageModel;
};