#include "Math3D.h"

namespace Math3d
{
	/// <summary>
	/// ベクトル同士の加算
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
	{
		VECTOR ret;
		ret.x = lhs.x + rhs.x;
		ret.y = lhs.y + rhs.y;
		ret.z = lhs.z + rhs.z;
		return ret;
	}

	/// <summary>
	/// ベクトル同士の減算
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
	{
		VECTOR ret;
		ret.x = lhs.x - rhs.x;
		ret.y = lhs.y - rhs.y;
		ret.z = lhs.z - rhs.z;
		return ret;
	}

	/// <summary>
	/// ベクトルのスカラー倍
	/// </summary>
	/// <param name="s"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	VECTOR operator*(float s, const VECTOR& rhs)
	{
		VECTOR ret;
		ret.x = s * rhs.x;
		ret.y = s * rhs.y;
		ret.z = s * rhs.z;
		return ret;
	}

	/// <summary>
	/// ベクトルのスカラー倍
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="s"></param>
	/// <returns></returns>
	VECTOR operator*(const VECTOR& lhs, float s)
	{
		VECTOR ret;
		ret.x = s * lhs.x;
		ret.y = s * lhs.y;
		ret.z = s * lhs.z;
		return ret;
	}

	/// <summary>
	/// += VECTORの演算子
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	/// <summary>
	/// *= VECTORのスカラー倍の複合代入演算子
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	VECTOR operator*=(VECTOR& lhs, float rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}
}