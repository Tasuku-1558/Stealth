#pragma once

#include "DxLib.h"

/// <summary>
/// エフェクトベースクラス
/// </summary>
class EffectBase
{
public:
	EffectBase() {/*処理なし*/ };
	virtual ~EffectBase() {/*処理なし*/ };

	virtual void Initialize() = 0;				//初期化処理
	virtual void Finalize() = 0;				//終了処理
	virtual void Activate() = 0;				//活性化処理
	virtual void Update(VECTOR pos) = 0;		//更新処理
	virtual void Draw() = 0;					//描画処理

private:
	EffectBase(const EffectBase&);		//コピーコンストラクタ
};