#pragma once

#include "DxLib.h"

/// <summary>
/// ���C�g�N���X
/// </summary>
class Light final
{
public:

	 Light();		//�R���X�g���N�^
	~Light();		//�f�X�g���N�^

	void Initialize();
	void Update(VECTOR enemyDir);
private:

	int lightHandle;

	//�ÓI�萔
	static const VECTOR DIRECTION;	//���C�g�̕���
};