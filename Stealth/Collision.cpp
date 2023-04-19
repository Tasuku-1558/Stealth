#include "Collision.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

namespace My3dLib
{
	/// <summary>
	/// ���̃R���X�g���N�^(�����Ȃ�)
	/// </summary>
	Sphere::Sphere()
		: radius(0.0f)
		, localCenter()
		, worldCenter()
	{
		//�����Ȃ�
	}

	/// <summary>
	/// ���̃R���X�g���N�^(��������)
	/// </summary>
	/// <param name="center">���S���W</param>
	/// <param name="radius">���a</param>
	Sphere::Sphere(const VECTOR& center, float radius)
		: radius(radius)
		, localCenter(center)
		, worldCenter(center)
	{
		//�����Ȃ�
	}

	/// <summary>
	/// ���̂̃��[���h���W���ړ�����
	/// </summary>
	/// <param name="position">���̂̈ʒu</param>
	void Sphere::Move(const VECTOR& position)
	{
		worldCenter = localCenter + position;
	}
}