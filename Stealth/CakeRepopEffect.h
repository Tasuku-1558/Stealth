#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// ケーキエフェクトクラス
/// ケーキ再スポーン時のエフェクト
/// </summary>
class CakeRepopEffect final : public EffectBase
{
public:
	CakeRepopEffect();
	virtual ~CakeRepopEffect();

	void Initialize();		//初期化処理
	void Activate();		//活性化処理

	void Update(float cakePosX, float cakePosY, float cakePosZ);			//更新処理
	void Draw();															//描画処理

private:

	CakeRepopEffect(const CakeRepopEffect&);		//コピーコンストラクタ
	void Finalize();								//終了処理


	int effectHandle;				//ケーキ再スポーン時エフェクト格納用
	int effectTime;					//エフェクト時間

	//ケーキ再スポーン時エフェクトの位置
	float effectPosX;
	float effectPosY;
	float effectPosZ;

	int playingEffectHandle;		// 再生中のエフェクトのハンドルを初期化

	//静的定数
	static const string EFFECT_FOLDER_PATH;		//effectフォルダまでのパス
	static const string CAKE_PATH;				//ケーキ再スポーン時エフェクトのパス
};