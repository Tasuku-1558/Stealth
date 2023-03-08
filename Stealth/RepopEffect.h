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
	RepopEffect(/*string effectPath, float effectSize*/);
	virtual ~RepopEffect();

	void Update(VECTOR pos)override;	//更新処理
	void Draw()override;				//描画処理

private:

	RepopEffect(const RepopEffect&);	//コピーコンストラクタ

	//定数
	const string EFFECT_FOLDER_PATH;	//effectフォルダまでのパス
	const string CAKE_PATH;				//ケーキ再スポーン時エフェクトのパス
	const float  MAGNIFICATION;			//エフェクトの拡大率
};