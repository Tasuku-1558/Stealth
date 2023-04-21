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

private:
	Light(const Light&);	//コピーコンストラクタ

	void Initialize();		//初期化処理

	//定数
	const VECTOR DIRECTION;	//ライトの向き
};