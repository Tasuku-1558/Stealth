#pragma once

#include "EffectBase.h"
#include <string>


using namespace std;

/// <summary>
/// エフェクト管理クラス
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	virtual ~EffectManager();

	//エフェクトの種類
	enum Effect
	{
		REPOP,				//リスポーンエフェクト(ケーキとプレイヤー)
		EFFECT_AMOUNT,		//エフェクトの種類
	};

	void Initialize();		//初期化処理
	void Draw();			//描画処理

	void CreateRepopEffect(VECTOR position);	//リスポーンエフェクトの生成

private:
	EffectManager(const EffectManager&);		//コピーコンストラクタ

	string InputPath(string folderPath, 
					 string effectPath);		//パスの入力


	EffectBase* effect[EFFECT_AMOUNT];			//エフェクト格納用


	//定数
	const string EFFECT_FOLDER_PATH;	//effectフォルダまでのパス
	const string REPOP_EFFECT_PATH;		//リスポーン時エフェクトのパス
	const float  REPOP_SIZE;			//リスポーンエフェクトのサイズ

};