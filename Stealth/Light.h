#pragma once

#include "DxLib.h"

//���C�g�N���X
class Light final
{
public:

	 Light();		//�R���X�g���N�^
	~Light();		//�f�X�g���N�^

	void Initialize();

private:

	//�ÓI�萔
	static const VECTOR DIRECTION;	//���C�g�̕���
};