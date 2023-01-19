#pragma once

#include "ObjectBase.h"


/// <summary>
/// 壁クラス
/// </summary>
class Wall final : public ObjectBase
{
public:

	 Wall(VECTOR pos);
	 virtual ~Wall();

	void Initialize();
	void Finalize();
	void Draw();

private:

	Wall(const Wall&);					//コピーコンストラクタ

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const VECTOR POSITION;		//モデルの位置

};