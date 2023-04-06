#pragma once

#include "EffectBase.h"

/// <summary>
/// エフェクト管理クラス
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	virtual ~EffectManager();

	//エフェクトの種類
	enum EffectType
	{
		RESPAWN,			//リスポーンエフェクト
		EFFECT_AMOUNT,		//エフェクトの種類
	};

	void Draw();			//描画処理

	void CreateEffect(VECTOR position, EffectType effectType);	//エフェクトの生成

private:
	EffectManager(const EffectManager&);		//コピーコンストラクタ

	void Initialize();							//初期化処理

	EffectBase* effect[EFFECT_AMOUNT];			//エフェクト格納用

	//エフェクト
	const string EFFECT_FOLDER_PATH;	//Effectフォルダまでのパス
	const string RESPAWN_EFFECT_PATH;	//リスポーンエフェクトのパス

	//エフェクトのサイズ
	const float  RESPAWN_SIZE;			//リスポーンエフェクトのサイズ

};