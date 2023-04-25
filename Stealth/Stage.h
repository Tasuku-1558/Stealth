#pragma once

#include "ObjectBase.h"

/// <summary>
/// ステージクラス
/// </summary>
class Stage final : public ObjectBase
{
public:
	Stage(VECTOR position);
	virtual ~Stage();

	void Draw();			//描画処理

private:
	Stage(const Stage&);	//コピーコンストラクタ
};