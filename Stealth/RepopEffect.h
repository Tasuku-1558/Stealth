#pragma once

#include "EffectBase.h"
#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// リスポーンエフェクトクラス
/// ケーキ再スポーン時のエフェクトとプレイヤーリスポーン時のエフェクト
/// </summary>
class RepopEffect final : public EffectBase
{
public:
	RepopEffect();
	virtual ~RepopEffect();

	void Initialize();			//初期化処理
	void Activate();			//活性化処理
	void Update(VECTOR pos);	//更新処理
	void Draw();				//描画処理

private:

	RepopEffect(const RepopEffect&);		//コピーコンストラクタ
	void Finalize();								//終了処理

	int effectHandle;					//ケーキ再スポーン時エフェクト格納用
	int effectTime;						//エフェクト時間

	int playingEffectHandle;			//再生中のエフェクトのハンドルを初期化

	//定数
	const string EFFECT_FOLDER_PATH;	//effectフォルダまでのパス
	const string CAKE_PATH;				//ケーキ再スポーン時エフェクトのパス
};