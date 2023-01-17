#pragma once

#include "DxLib.h"

/// <summary>
/// ライトクラス
/// </summary>
class Light final
{
public:

	 Light();		//コンストラクタ
	~Light();		//デストラクタ

	void Initialize();
	void Update(VECTOR enemyDir);
private:

	int lightHandle;

	//静的定数
	static const VECTOR DIRECTION;	//ライトの方向
};