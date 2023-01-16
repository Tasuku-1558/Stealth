#pragma once

#include "ObjectBase.h"

/// <summary>
/// ボールクラス
/// </summary>
class Ball final : public ObjectBase
{
public:
	 Ball(const VECTOR& pos);
	~Ball();

	void Initialize();
	void Finalize();
	void Update(bool hit);
	void SetDead();							//ボールを非アクティブ化
	void Draw();

	bool GetAlive() { return alive; }

private:

	Ball(const Ball&);								//コピーコンストラクタ
	void IsAlive(bool hit);			//生きてるか死んでいるか

	bool alive;										//ボールが生きてるか死んでいるか

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const VECTOR POSITION;		//モデルの位置
};