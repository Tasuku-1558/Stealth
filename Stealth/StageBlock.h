#pragma once

#include "ObjectBase.h"

/// <summary>
/// ステージブロッククラス
/// </summary>
class StageBlock final : public ObjectBase
{
public:
	StageBlock(VECTOR position, VECTOR scale);
	virtual ~StageBlock();

	void Update(float deltaTime);	//更新処理
	void Draw();					//描画処理

private:
	StageBlock(const StageBlock&);	//コピーコンストラクタ
};