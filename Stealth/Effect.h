#pragma once

#include "EffectBase.h"

/// <summary>
/// エフェクトクラス
/// </summary>
class Effect final : public EffectBase
{
public:
	Effect(string effectPath, float effectSize);
	virtual ~Effect();

	void Update(VECTOR position)override;	//更新処理
	void Draw()override;					//描画処理

private:

	Effect(const Effect&);	//コピーコンストラクタ
};