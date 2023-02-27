#pragma once

#include "DxLib.h"
#include "ParticleBase.h"


/// <summary>
/// ケーキパーティクルクラス
/// ケーキ発射時に出すパーティクル
/// </summary>
class CakeParticle final : public ParticleBase
{
public:
	CakeParticle(const VECTOR& pos);
	virtual ~CakeParticle();

	void Initialize()override;				//初期化処理
	void Activate()override;				//活性化処理
	void Update(float deltaTime)override;	//更新処理
	void Draw()override;					//描画処理

private:
	CakeParticle(const CakeParticle&);	//コピーコンストラクタ

	float particlePopTime;				//パーティクルの出現時間

	//定数
	const unsigned int PINK;			//パーティクルのカラー
};