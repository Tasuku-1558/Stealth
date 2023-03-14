#pragma once

#include "ObjectBase.h"
#include "Collision.h"

/// <summary>
/// ケーキクラス
/// </summary>
class Cake final : public ObjectBase
{
public:
	Cake(const VECTOR& cakePosition);
	virtual ~Cake();

	void Initialize();					//初期化処理
	void Activate();					//活性化処理
	void Finalize();					//終了処理
	void Update(float deltaTime);		//更新処理
	void CakeAlive();					//ケーキをアクティブ化
	void Draw();						//描画処理
	void HitCake();						//ケーキに衝突した

	const bool GetAlive() { return alive; }									//ケーキが生きてるか死んでるかを返す
	const float GetCollideRadius() { return collisionSphere.radius; }		//当たり判定球の半径を返す

private:

	Cake(const Cake&);			//コピーコンストラクタ

	bool alive;					//ケーキが生きてるか死んでいるか

	My3dLib::Sphere collisionSphere;	//当たり判定球

	//定数
	const VECTOR SIZE;          //モデルの倍率
	const VECTOR ROTATE;		//モデルの回転値
	const float  RADIUS;		//ケーキの半径

};