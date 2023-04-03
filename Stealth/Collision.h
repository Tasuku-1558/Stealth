#pragma once

#include "DxLib.h"
#include "Math3D.h"

namespace My3dLib
{
	//���̂̓����蔻��
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);

		void Move(const VECTOR& position);	//���̂̃��[���h���W���ړ�����

		VECTOR localCenter; //���̂̃��[�J�����S���W
		VECTOR worldCenter; //���̂̃��[���h���S���W
		float  radius;      //���̂̔��a
	};
}