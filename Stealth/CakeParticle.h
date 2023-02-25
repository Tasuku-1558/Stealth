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

	void Initialize();				//初期化処理
	void Activate();				//活性化処理
	void Update(float deltaTime);	//更新処理
	void Draw();					//描画処理

private:
	CakeParticle(const CakeParticle&);	//コピーコンストラクタ

	//定数
	const unsigned int PINK;		//パーティクルのカラー
};