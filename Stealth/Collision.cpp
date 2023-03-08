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
	/// <param name="center"></param>
	/// <param name="radius"></param>
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
	/// <param name="pos"></param>
	void Sphere::Move(const VECTOR& pos)
	{
		worldCenter = localCenter + pos;
	}

	/// <summary>
	/// カプセルコンストラクタ(引数なし)
	/// </summary>
	Capsule::Capsule()
		: localStart()
		, localEnd()
		, worldStart()
		, worldEnd()
		, radius(0.0f)
	{
		//処理なし
	}

	/// <summary>
	/// カプセルコンストラクタ(引数あり)
	/// </summary>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <param name="radius"></param>
	Capsule::Capsule(const VECTOR& start, const VECTOR& end, float radius)
		: localStart()
		, localEnd()
		, worldStart()
		, worldEnd()
		, radius(0.0f)
	{
		//処理なし
	}

	/// <summary>
	/// 当たり判定 球・球
	/// </summary>
	/// <param name="sphere1"></param>
	/// <param name="sphere2"></param>
	/// <returns></returns>
	bool CollisionSphereAndSphere(const Sphere& sphere1, const Sphere& sphere2)
	{
		return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.radius,
			sphere2.worldCenter, sphere2.radius);
	}

	/// <summary>
	/// 当たり判定 球・カプセル
	/// </summary>
	/// <param name="sphere"></param>
	/// <param name="capsule"></param>
	/// <returns></returns>
	bool CollisionCapsuleAndSphere(const Sphere& sphere, const Capsule& capsule)
	{
		return HitCheck_Sphere_Capsule(sphere.worldCenter, sphere.radius,
			capsule.worldStart, capsule.worldEnd, capsule.radius);
	}
}