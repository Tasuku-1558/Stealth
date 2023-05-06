#pragma once

#include "ParticleBase.h"

/// <summary>
/// 花火パーティクルクラス
/// リザルト画面で出すパーティクル
/// </summary>
class FireWorksParticle final : public ParticleBase
{
public:
	FireWorksParticle(const VECTOR& particlePosition, unsigned int particleColor);
	virtual ~FireWorksParticle();

	void Update(float deltaTime)override;	//更新処理
	void Draw()override;					//描画処理
	void DeleteParticle()override;			//削除処理

private:
	FireWorksParticle(const FireWorksParticle&);	//コピーコンストラクタ

	void Initialize()override;			//初期化処理

	unsigned int color;					//パーティクルの色

	//定数
	const float MAX_POP_TIME;		//パーティクルの最大出現時間
	const float POSITION_Y;			//パーティクルのY座標
};