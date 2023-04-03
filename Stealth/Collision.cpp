#include "Collision.h"

using namespace Math3d;		//VECTORの計算に使用

namespace My3dLib
{
	/// <summary>
	/// 球体コンストラクタ(引数なし)
	/// </summary>
	Sphere::Sphere()
		: localCenter()
		, worldCenter()
		, radius(0.0f)
	{
		//処理なし
	}

	/// <summary>
	/// 球体コンストラクタ(引数あり)
	/// </summary>
	/// <param name="center">中心座標</param>
	/// <param name="radius">半径</param>
	Sphere::Sphere(const VECTOR& center, float radius)
		: localCenter(center)
		, worldCenter(center)
		, radius(radius)
	{
		//処理なし
	}

	/// <summary>
	/// 球体のワールド座標を移動する
	/// </summary>
	/// <param name="position">球体の位置</param>
	void Sphere::Move(const VECTOR& position)
	{
		worldCenter = localCenter + position;
	}
}