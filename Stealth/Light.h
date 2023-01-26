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

	void Initialize(VECTOR direction);				//初期化処理
	void SelectionLight(VECTOR direction);

private:
	
	//静的定数
	static const VECTOR DIRECTION;	//ライトの方向
};