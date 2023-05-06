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
	void DeleteParticle()override;			//削除処理

private:
	CakeParticle(const CakeParticle&);	//コピーコンストラクタ

	void Initialize()override;			//初期化処理


	//定数
	const unsigned int PINK;		//パーティクルのカラー
	const float MAX_POP_TIME;		//パーティクルの最大出現時間
	const float POSITION_Y;			//パーティクルのY座標
};