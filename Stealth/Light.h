#pragma once

#include "DxLib.h"

//ライトクラス
class Light final
{
public:

	 Light();		//コンストラクタ
	~Light();		//デストラクタ

	void Initialize();

private:

	//静的定数
	static const VECTOR DIRECTION;	//ライトの方向
};