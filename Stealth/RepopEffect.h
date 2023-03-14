#pragma once

#include "EffectBase.h"
#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// リスポーンエフェクトクラス
/// ケーキ再スポーン時のエフェクトとプレイヤーリスポーン時のエフェクトに使用している
/// </summary>
class RepopEffect final : public EffectBase
{
public:
	RepopEffect(string effectPath, float effectSize);
	virtual ~RepopEffect();

	void Update(VECTOR position)override;	//更新処理
	void Draw()override;					//描画処理

private:

	RepopEffect(const RepopEffect&);	//コピーコンストラクタ
};