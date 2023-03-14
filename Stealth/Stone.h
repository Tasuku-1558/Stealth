#pragma once

#include "ObjectBase.h"
#include "Collision.h"

/// <summary>
/// 小石クラス
/// </summary>
class Stone final : public ObjectBase
{
public:
	Stone(const VECTOR& stonePosition);
	virtual ~Stone();

	void Initialize();					//初期化処理
	void Activate();					//活性化処理
	void Finalize();					//終了処理
	void Update(float deltaTime);		//更新処理
	void StoneAlive();					//小石をアクティブ化
	void Draw();						//描画処理

	const bool GetAlive() { return alive; }			//小石が生きてるか死んでるかを返す
	const float GetCollideRadius() { return collisionSphere.radius; }		//当たり判定球の半径を返す

private:

	Stone(const Stone&);		//コピーコンストラクタ

	bool alive;					//小石が生きてるか死んでいるか

	My3dLib::Sphere collisionSphere;		//当たり判定球

	//定数
	const VECTOR SIZE;      //モデルの倍率
	const VECTOR ROTATE;	//モデルの回転値
	const float  RADIUS;	//小石の半径
};