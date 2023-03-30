#pragma once

#include "ParticleBase.h"


/// <summary>
/// ケーキパーティクルクラス
/// ケーキ発射時に出すパーティクル
/// </summary>
class CakeParticle final : public ParticleBase
{
public:
	CakeParticle(const VECTOR& particlePosition);
	virtual ~CakeParticle();

	void Update(float deltaTime)override;	//更新処理
	void Draw()override;					//描画処理

private:
	CakeParticle(const CakeParticle&);	//コピーコンストラクタ

	void Initialize()override;				//初期化処理

	float particlePopTime;				//パーティクルの出現時間

	//定数
	const unsigned int PINK;			//パーティクルのカラー
	const float POS_Y;					//パーティクルのY座標
};