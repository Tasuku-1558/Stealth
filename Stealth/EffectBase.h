#pragma once

#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// エフェクト基底クラス
/// </summary>
class EffectBase
{
public:
	EffectBase();
	virtual ~EffectBase();

	virtual void Update(VECTOR position) = 0;		//更新処理
	virtual void Draw() = 0;						//描画処理

protected:

	int effectHandle;					//エフェクトハンドル
	int playingEffectHandle;			//再生中のエフェクトのハンドルを初期化
	int effectTime;						//エフェクト時間

private:
	EffectBase(const EffectBase&);		//コピーコンストラクタ
};