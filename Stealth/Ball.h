#pragma once

#include "ObjectBase.h"

class HitChecker;

/// <summary>
/// ボールクラス
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball(VECTOR pos);
	 virtual ~Ball();

	void Initialize();					//初期化処理
	void Activate();					//活性化処理
	void Finalize();					//終了処理
	void Update();						//更新処理
	void BallAlive();					//ボールをアクティブ化
	void Draw();						//描画処理

	const bool GetAlive() { return alive; }			//ボールが生きてるか死んでるかを返す
	void IsAlive(HitChecker* hitChecker);			//ボールが生きてるか死んでいるかを判定

private:

	Ball(const Ball&);					//コピーコンストラクタ

	bool alive;							//ボールが生きてるか死んでいるか


	//静的定数
	static const VECTOR SIZE;           //モデルの倍率

};