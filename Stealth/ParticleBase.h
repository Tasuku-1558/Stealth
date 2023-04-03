#pragma once

#include "DxLib.h"
#include "Math3D.h"
#include <math.h>

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// パーティクル基底クラス
/// </summary>
class ParticleBase
{
public:

	ParticleBase();
	virtual ~ParticleBase();

	virtual void Initialize() = 0;				//初期化処理
	virtual void Update(float deltaTime) = 0;	//更新処理
	virtual void Draw() = 0;					//描画処理

	const bool IsParticleEnd() { return endFlag; }		//パーティクルを消すフラグを返す

protected:

	float  radius;				//半径
	float  particlePopCount;	//パーティクル出現カウント
	float  xPower;				//横方向の力
	float  zPower;				//縦方向の力
	bool   endFlag;				//消すか消さないか
	VECTOR position;			//位置

	//定数
	const int DIVNUM;		//ポリゴンの細かさ
	const int ALPHA;		//アルファブレンド
	const int NOBLEND;		//デフォルトブレンド処理
};