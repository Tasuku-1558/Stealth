#pragma once

#include "ObjectBase.h"
#include "Math3D.h"

class Boal;

/// <summary>
/// プレイヤーショットクラス
/// </summary>
class Bullet final : public ObjectBase
{
public:
	 Bullet();
	~Bullet();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition, VECTOR inDir);
	void Update(float deltaTime, Boal* boal);
	void Draw();


private:

	void OnShot(float deltaTime);			//球が撃たれた時

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const float  SPEED;			//モデルのスピード

};