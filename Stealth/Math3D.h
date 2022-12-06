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
}