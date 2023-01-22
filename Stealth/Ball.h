#pragma once

#include "ObjectBase.h"

/// <summary>
/// ボールクラス
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball(VECTOR pos);
	 virtual ~Ball();

	void Initialize();
	void Activate();
	void Finalize();
	void Update();
	void SetAlive();							//ボールをアクティブ化
	void Draw();

	bool GetAlive() { return alive; }
	void IsAlive(bool hit);			//生きてるか死んでいるか

private:

	Ball(const Ball&);								//コピーコンストラクタ

	bool alive;										//ボールが生きてるか死んでいるか

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
};