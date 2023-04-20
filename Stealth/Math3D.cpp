#include "Math3D.h"

namespace Math3d
{
	/// <summary>
	/// �x�N�g�����m�̉��Z
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
	/// �x�N�g�����m�̌��Z
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
	/// �x�N�g���̃X�J���[�{
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
	/// �x�N�g���̃X�J���[�{
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
	/// += VECTOR�̉��Z�q
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
	/// *= VECTOR�̃X�J���[�{�̕���������Z�q
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
	/// 2�̃x�N�g���̊p�x�͂قړ�����
	/// �قȂ��false��Ԃ�
	/// </summary>
	/// <param name="v1">1�ڂ̃x�N�g���̊p�x</param>
	/// <param name="v2">2�ڂ̃x�N�g���̊p�x</param>
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
	/// nowVec����nextVec�̍ŒZ�̉�]�����𒲂ׂ�iY����]��z��)
	/// ���v���̎���1.0�A�����v���̎���-1.0��Ԃ�
	/// </summary>
	/// <param name="nowVec">���݂̃x�N�g��</param>
	/// <param name="nextVec">�����̃x�N�g��</param>
	/// <returns>�ŒZ�̉�]������Ԃ�</returns>
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
	/// nowVec����nextVec�Ɍ�������degreeVerociy�̑��x��Y��]����
	/// </summary>
	/// <param name="nowVec">���݂̃x�N�g��</param>
	/// <param name="nextVec">�����̃x�N�g��</param>
	/// <param name="degreeVerocity">�x�����x</param>
	/// <returns>Y����]�x�N�g����Ԃ�</returns>
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& nextVec, float degreeVerocity)
	{
		//�p���x�i�x���j�����W�A���p�ɕϊ��A�E��肩����肩�𒲂ׂ�
		float rotateRadian = (DX_PI_F * degreeVerocity / 180.0f);
		rotateRadian *= CalcRotationDirectionYAxis(nowVec, nextVec);

		//Y����]�s����쐬
		MATRIX yRotateMat = MGetRotY(rotateRadian);

		//Y����]
		VECTOR rotateVec = VTransform(nowVec, yRotateMat);

		return rotateVec;
	}
}