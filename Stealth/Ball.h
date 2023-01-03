#pragma once

#include "ObjectBase.h"

class HitChecker;

/// <summary>
/// ボールクラス
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball();
	~Ball();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(HitChecker* hitChecker);
	void Draw();

	bool GetAlive() { return alive; }

private:

	void IsAlive(HitChecker* hitChecker);			//生きてるか死んでいるか

	bool alive;										//ボールが生きてるか死んでいるか

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const VECTOR POSITION;		//モデルの位置
};