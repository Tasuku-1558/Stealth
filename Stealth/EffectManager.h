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
		SHOT,				//ケーキ発射エフェクト
		EFFECT_AMOUNT,		//エフェクトの種類
	};

	void Draw();			//描画処理

	void CreateEffect(VECTOR position, EffectType effectType);	//エフェクトの生成

private:
	EffectManager(const EffectManager&);	//コピーコンストラクタ

	void Initialize();					//初期化処理
	void DeleteEffect();				//エフェクトの削除

	EffectBase* effect[EFFECT_AMOUNT];	//エフェクト格納用

	struct Effects
	{
		string effectPath;	//エフェクトのパス
		float  effectSize;	//エフェクトのサイズ
	};

	//エフェクト
	const string EFFECT_FOLDER_PATH;	//Effectフォルダまでのパス
	const string RESPAWN_EFFECT_PATH;	//リスポーンエフェクトのパス
	const string SHOT_EFFECT_PATH;		//ケーキ発射エフェクトのパス

	//エフェクトのサイズ
	const float  RESPAWN_SIZE;			//リスポーンエフェクトのサイズ
	const float  SHOT_SIZE;				//ケーキ発射エフェクトのサイズ

};