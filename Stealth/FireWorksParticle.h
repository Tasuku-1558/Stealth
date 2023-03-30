#pragma once

#include "ParticleBase.h"

/// <summary>
/// 花火パーティクルクラス
/// リザルト画面で出すパーティクル
/// </summary>
class FireWorksParticle final : public ParticleBase
{
public:
	FireWorksParticle(const VECTOR particlePosition, unsigned int changeColor);
	virtual ~FireWorksParticle();

	void Update(float deltaTime)override;	//更新処理
	void Draw()override;					//描画処理

private:
	FireWorksParticle(const FireWorksParticle&);	//コピーコンストラクタ

	void Initialize()override;				//初期化処理

	float particlePopTime;				//パーティクルの出現時間
	unsigned int color;					//パーティクルの色

	//定数
	const float POS_Y;					//パーティクルのY座標
};