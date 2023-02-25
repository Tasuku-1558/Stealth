#pragma once

#include "ObjectBase.h"
#include "Math3D.h"


/// <summary>
/// �S�[���t���b�O�N���X
/// </summary>
class GoalFlag final : public ObjectBase
{
public:
	GoalFlag(VECTOR pos);
	virtual ~GoalFlag();

	void Initialize();					//����������
	void Finalize();					//�I������
	void Update(float deltaTime);		//�X�V����
	void Draw();						//�`�揈��

private:
	GoalFlag(const GoalFlag&);			//�R�s�[�R���X�g���N�^

	VECTOR rotate;						//���f���̉�]


	//�萔
	const VECTOR SIZE;           //���f���̔{��
	const VECTOR ROTATE_SPEED;	 //���f���̉�]�X�s�[�h

};