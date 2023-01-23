#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// ボールエフェクトクラス
/// ボール再スポーン時のエフェクト
/// </summary>
class Effect final : public EffectBase
{
public:
	Effect();
	virtual ~Effect();

	void Initialize();		//初期化処理
	void Finalize();		//終了処理
	void Activate();		//活性化処理

	void Update(float ballPosX, float ballPosY, float ballPosZ);			//更新処理
	void Draw();															//描画処理

private:

	int effectHandle;				//ボール再スポーン時エフェクト格納用
	int effectTime;					//エフェクト時間

	//ボール再スポーン時エフェクトの位置
	float effectPos_X;
	float effectPos_Y;
	float effectPos_Z;

	int playingEffectHandle;		// 再生中のエフェクトのハンドルを初期化


	//静的定数
	static const string EFFECT_FOLDER_PATH;		//effectフォルダまでのパス
	static const string BALL_PATH;				//ボール再スポーン時エフェクトのパス

};