#pragma once

#include "ObjectBase.h"

class HitChecker;

/// <summary>
/// ボールクラス
/// </summary>
class Boal final : public ObjectBase
{
public:
	 Boal();
	~Boal();

	void Initialize();
	void Finalize();
	void Activate();
	void Update();
	void Draw();

	bool GetAlive() { return alive; }

private:

	void IsAlive(HitChecker* hitChecker);			//生きてるか死んでいるか

	bool alive;			//ボールが生きてるか死んでいるか

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const VECTOR POSITION;		//モデルの位置
};