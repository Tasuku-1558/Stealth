#include "Math3D.h"

namespace Math3d
{
	// �x�N�g�����m�̉��Z
	VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
	{
		VECTOR ret;
		ret.x = lhs.x + rhs.x;
		ret.y = lhs.y + rhs.y;
		ret.z = lhs.z + rhs.z;
		return ret;
	}

	// �x�N�g�����m�̌��Z
	VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
	{
		VECTOR ret;
		ret.x = lhs.x - rhs.x;
		ret.y = lhs.y - rhs.y;
		ret.z = lhs.z - rhs.z;
		return ret;
	}

	// �x�N�g���̃X�J���[�{
	VECTOR operator*(float s, const VECTOR& rhs)
	{
		VECTOR ret;
		ret.x = s * rhs.x;
		ret.y = s * rhs.y;
		ret.z = s * rhs.z;
		return ret;
	}

	// �x�N�g���̃X�J���[�{
	VECTOR operator*(const VECTOR& lhs, float s)
	{
		VECTOR ret;
		ret.x = s * lhs.x;
		ret.y = s * lhs.y;
		ret.z = s * lhs.z;
		return ret;
	}

	// += VECTOR�̉��Z�q
	VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	// *= VECTOR�̃X�J���[�{�̕���������Z�q
	VECTOR operator*=(VECTOR& lhs, float rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
}