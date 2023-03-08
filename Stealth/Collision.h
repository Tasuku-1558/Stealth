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

	//�J�v�Z���̓����蔻��
	struct Capsule
	{
		Capsule();
		Capsule(const VECTOR& start, const VECTOR& end, float radius);

		VECTOR localStart; //�J�v�Z���̃��[�J���J�n���W
		VECTOR worldStart; //�J�v�Z���̃��[���h�J�n���W
		VECTOR localEnd;   //�J�v�Z���̃��[�J���I�����W
		VECTOR worldEnd;   //�J�v�Z���̃��[���h�I�����W
		float  radius;     //�J�v�Z���̔��a
	};

	//�����蔻��̊֐��g�ݍ��킹
	bool CollisionSphereAndSphere(const Sphere& sphere1, const Sphere& sphere2);
	bool CollisionCapsuleAndSphere(const Sphere& sphere, const Capsule& capsule);

}