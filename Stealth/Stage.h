#pragma once

#include "ObjectBase.h"

/// <summary>
/// ステージブロッククラス
/// </summary>
class Stage final : public ObjectBase
{
public:
	Stage(VECTOR position);
	virtual ~Stage();

	void Draw();			//描画処理

	MV1_COLL_RESULT_POLY_DIM Get() { return hitPolyDim; }

private:
	Stage(const Stage&);	//コピーコンストラクタ

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};