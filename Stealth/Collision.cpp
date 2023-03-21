#include "Collision.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

namespace My3dLib
{
	/// <summary>
	/// ���̃R���X�g���N�^(�����Ȃ�)
	/// </summary>
	Sphere::Sphere()
		: localCenter()
		, worldCenter()
		, radius(0.0f)
	{
		//�����Ȃ�
	}

	/// <summary>
	/// ���̃R���X�g���N�^(��������)
	/// </summary>
	/// <param name="center"></param>
	/// <param name="radius"></param>
	Sphere::Sphere(const VECTOR& center, float radius)
		: localCenter(center)
		, worldCenter(center)
		, radius(radius)
	{
		//�����Ȃ�
	}

	/// <summary>
	/// ���̂̃��[���h���W���ړ�����
	/// </summary>
	/// <param name="pos"></param>
	void Sphere::Move(const VECTOR& pos)
	{
		worldCenter = localCenter + pos;
	}

	/// <summary>
	/// �����蔻�� ���E��
	/// </summary>
	/// <param name="sphere1"></param>
	/// <param name="sphere2"></param>
	/// <returns></returns>
	bool CollisionSphereAndSphere(const Sphere& sphere1, const Sphere& sphere2)
	{
		return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.radius,
			sphere2.worldCenter, sphere2.radius);
	}
}