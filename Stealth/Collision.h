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

		void Move(const VECTOR& pos);					//���̂̃��[���h���W���ړ�����

		VECTOR localCenter; //���̂̃��[�J�����S���W
		VECTOR worldCenter; //���̂̃��[���h���S���W
		float  radius;      //���̂̔��a
	};

	//�����蔻��̊֐��g�ݍ��킹
	bool CollisionSphereAndSphere(const Sphere& sphere1, const Sphere& sphere2);
}