#pragma once

#include "DxLib.h"

/// <summary>
/// ライトクラス
/// </summary>
class Light final
{
public:

	 Light();
	 virtual ~Light();

	void Update(VECTOR direction);	//更新処理

private:

};