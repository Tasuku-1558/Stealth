#pragma once

#include "ObjectBase.h"
#include "Math3D.h"
#include "Collision.h"

/// <summary>
/// ゴールフラッグクラス
/// </summary>
class GoalFlag final : public ObjectBase
{
public:
	GoalFlag(VECTOR pos);
	virtual ~GoalFlag();

	void Update(float deltaTime);		//更新処理
	void Draw();						//描画処理

	const float GetCollideRadius() { return collisionSphere.radius; }		//当たり判定球の半径を返す

private:
	GoalFlag(const GoalFlag&);			//コピーコンストラクタ

	void Initialize();					//初期化処理
	void Activate();					//活性化処理
	void Finalize();					//終了処理

	VECTOR rotate;						//モデルの回転

	My3dLib::Sphere collisionSphere;	//当たり判定球

	//定数
	const VECTOR SIZE;				//モデルの倍率
	const VECTOR ROTATE_SPEED;		//モデルの回転スピード
	const float  RADIUS;			//ゴールフラグの半径

};