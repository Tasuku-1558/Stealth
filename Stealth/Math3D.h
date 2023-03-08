#pragma once

#include "DxLib.h"

namespace Math3d
{
	//�x�N�g�����m�̉��Z
	VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

	//�x�N�g�����m�̌��Z
	VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

	//�x�N�g���̃X�J���[�{
	VECTOR operator*(float s, const VECTOR& rhs);

	//�x�N�g���̃X�J���[�{
	VECTOR operator*(const VECTOR& lhs, float s);

	//+= VECTOR�̉��Z�q
	VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

	//*= VECTOR�̃X�J���[�{�̕���������Z�q
	VECTOR operator*=(VECTOR& lhs, float rhs);

	//2�̃x�N�g���̊p�x�͂قړ�����
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);

	//nowVec����nextVec�̍ŒZ�̉�]�����𒲂ׂ�iY����]��z��)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& nextVec);

	//nowVec����nextVec�Ɍ�������degreeVerociy�̑��x��Y��]����
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& nextVec, float degreeVerocity);
}