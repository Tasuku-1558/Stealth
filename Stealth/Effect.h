#pragma once

#include "EffectBase.h"
#include <string>

using namespace std;

/// <summary>
/// ボールエフェクトクラス
/// </summary>
class Effect final : public EffectBase
{
public:
	Effect();
	virtual ~Effect();

	void Initialize();		//初期化
	void Finalize();
	void Activate();

	void Update(float ballPosX, float ballPosY, float ballPosZ);			//更新
	void Draw();			//描画

private:

	int effectHandle;				//ボール消失エフェクト格納用
	int effectTime;					//エフェクト時間

	//ボール消失エフェクトの位置
	float effectPos_X;
	float effectPos_Y;
	float effectPos_Z;

	int playingEffectHandle;		// 再生中のエフェクトのハンドルを初期化


	//静的定数
	static const string EFFECT_FOLDER_PATH;		//effectフォルダまでのパス
	static const string BALL_PATH;			//ボール消失エフェクトのパス

};