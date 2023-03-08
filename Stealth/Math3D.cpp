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

	/// <summary>
	/// 2つのベクトルの角度はほぼ同じか
	/// 異なればfalseを返す
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2)
	{
		float dot = VDot(v1, v2);

		if (dot > 0.99f)
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// nowVecからnextVecの最短の回転方向を調べる（Y軸回転を想定)
	/// 時計回りの時は1.0、反時計回りの時は-1.0を返す
	/// </summary>
	/// <param name="nowVec"></param>
	/// <param name="nextVec"></param>
	/// <returns></returns>
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& nextVec)
	{
		VECTOR axis = VCross(nowVec, nextVec);

		if (axis.y < 0.0f)
		{
			return -1.0f;
		}

		return 1.0f;
	}

	/// <summary>
	/// nowVecからnextVecに向かってdegreeVerociyの速度でY回転する
	/// </summary>
	/// <param name="nowVec"></param>
	/// <param name="nextVec"></param>
	/// <param name="degreeVerocity"></param>
	/// <returns></returns>
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& nextVec, float degreeVerocity)
	{
		//角速度（度数）をラジアン角に変換、右回りか左回りかを調べる
		float rotRadian = (DX_PI_F * degreeVerocity / 180.0f);
		rotRadian *= CalcRotationDirectionYAxis(nowVec, nextVec);

		//Y軸回転行列を作成する
		MATRIX yrotMat = MGetRotY(rotRadian);

		//Y軸回転する
		VECTOR rotVec = VTransform(nowVec, yrotMat);

		return rotVec;
	}
}