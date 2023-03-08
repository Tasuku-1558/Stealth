#pragma once

#include "DxLib.h"

namespace Math3d
{
	//ベクトル同士の加算
	VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

	//ベクトル同士の減算
	VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

	//ベクトルのスカラー倍
	VECTOR operator*(float s, const VECTOR& rhs);

	//ベクトルのスカラー倍
	VECTOR operator*(const VECTOR& lhs, float s);

	//+= VECTORの演算子
	VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

	//*= VECTORのスカラー倍の複合代入演算子
	VECTOR operator*=(VECTOR& lhs, float rhs);

	//2つのベクトルの角度はほぼ同じか
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);

	//nowVecからnextVecの最短の回転方向を調べる（Y軸回転を想定)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& nextVec);

	//nowVecからnextVecに向かってdegreeVerociyの速度でY回転する
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& nextVec, float degreeVerocity);
}