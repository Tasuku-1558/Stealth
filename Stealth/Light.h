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

	void Initialize();				//����������

private:

	//�ÓI�萔
	static const VECTOR DIRECTION;	//���C�g�̕���
};