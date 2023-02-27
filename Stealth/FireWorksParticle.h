#pragma once

#include "DxLib.h"
#include "ParticleBase.h"

/// <summary>
/// 花火パーティクルクラス
/// リザルト画面で出すパーティクル
/// </summary>
class FireWorksParticle final : public ParticleBase
{
public:
	FireWorksParticle(const VECTOR pos, unsigned int changeColor);
	virtual ~FireWorksParticle();

	void Initialize()override;				//初期化処理
	void Activate()override;				//活性化処理
	void Update(float deltaTime)override;	//更新処理
	void Draw()override;					//描画処理

private:
	FireWorksParticle(const FireWorksParticle&);	//コピーコンストラクタ


	float particlePopTime;				//パーティクルの出現時間
	unsigned int color;					//パーティクルの色
};