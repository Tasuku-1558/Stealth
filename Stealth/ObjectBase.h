#pragma once

#include "DxLib.h"
#include "PreCompiledHeader.h"

/// <summary>
/// ObjectBase�N���X
/// </summary>
class ObjectBase
{
public:
	ObjectBase();
	virtual~ObjectBase();
	
	//virtual void Update(float dltaTime) = 0;		//�X�V����
	virtual void Draw() = 0;						//�`�揈��
	
	const VECTOR& GetPosition()  const { return position; }
	const VECTOR& GetDirection() const { return direction; }
	const int& GetModelHandle()  const { return modelHandle; }

protected:

	int	   modelHandle;	//���f���n���h��
	VECTOR position;	//���݂̍��W
	VECTOR direction;	//�����x�N�g��
};