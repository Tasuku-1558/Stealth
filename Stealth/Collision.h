#pragma once

#include "DxLib.h"
#include "Math3D.h"

namespace My3dLib
{
	//球体の当たり判定
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);

		void Move(const VECTOR& position);	//球体のワールド座標を移動する

		VECTOR localCenter; //球体のローカル中心座標
		VECTOR worldCenter; //球体のワールド中心座標
		float  radius;      //球体の半径
	};
}