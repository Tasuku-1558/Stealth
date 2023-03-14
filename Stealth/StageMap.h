#pragma once

#include "StageBase.h"
#include "ModelManager.h"


/// <summary>
/// �X�e�[�W�}�b�v�N���X
/// </summary>
class StageMap final : public StageBase
{
public:
	StageMap(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position);
	virtual ~StageMap();

	void Initialize();      //����������
	void Draw();            //�`�揈��

private:
	StageMap(const StageMap&);				//�R�s�[�R���X�g���N�^

	void Finalize();						//�I������

	int kabe;
	int frameNo;

};