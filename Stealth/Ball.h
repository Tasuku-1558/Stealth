#pragma once

#include "ObjectBase.h"
#include "HitChecker.h"


/// <summary>
/// ボールクラス
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball(VECTOR pos);
	~Ball();

	void Initialize();
	void Finalize();
	void Update(HitChecker* hitChecker);
	void SetDead();							//ボールを非アクティブ化
	void Draw();

	bool GetAlive() { return alive; }

private:

	Ball(const Ball&);								//コピーコンストラクタ
	void IsAlive(HitChecker* hitChecker);			//生きてるか死んでいるか

	bool alive;										//ボールが生きてるか死んでいるか

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const VECTOR POSITION;		//モデルの位置
};