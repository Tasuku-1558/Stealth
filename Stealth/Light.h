#pragma once

#include "DxLib.h"

/// <summary>
/// ���C�g�N���X
/// </summary>
class Light final
{
public:
	Light();
	virtual ~Light();

private:
	Light(const Light&);	//�R�s�[�R���X�g���N�^

	void Initialize();		//����������

	//�萔
	const VECTOR DIRECTION;	//���C�g�̌���
};