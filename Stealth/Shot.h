#pragma once

#include "ObjectBase.h"
#include "Math3D.h"


/// <summary>
/// プレイヤーショットクラス
/// </summary>
class Shot final : public ObjectBase
{
public:
	 Shot();
	~Shot();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(VECTOR position);
	void Draw();


private:

	void OnShot(VECTOR position);			//球が撃たれた時

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	//static const VECTOR POSITION;		//モデルの位置
	static const float  SPEED;			//モデルのスピード
	static const VECTOR DIR;

};