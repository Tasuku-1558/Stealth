#pragma once

#include "ObjectBase.h"


/// <summary>
/// 壁クラス
/// </summary>
class Wall final : public ObjectBase
{
public:

	 Wall(Object WALL);
	~Wall();

	void Initialize();
	void Finalize();
	void Draw();

private:

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const VECTOR POSITION;		//モデルの位置

};