#pragma once

#include "ObjectBase.h"

class HitChecker;

/// <summary>
/// ケーキクラス
/// </summary>
class Cake final : public ObjectBase
{
public:
	Cake(const VECTOR& pos);
	virtual ~Cake();

	void Initialize();					//初期化処理
	void Activate();					//活性化処理
	void Finalize();					//終了処理
	void Update(float deltaTime);		//更新処理
	void CakeAlive();					//ケーキをアクティブ化
	void Draw();						//描画処理
	void IsAlive(HitChecker* hitChecker);			//ケーキが生きてるか死んでいるかを判定

	const bool GetAlive() { return alive; }			//ケーキが生きてるか死んでるかを返す

private:

	Cake(const Cake&);			//コピーコンストラクタ

	bool alive;					//ケーキが生きてるか死んでいるか


	//定数
	const VECTOR SIZE;           //モデルの倍率

};