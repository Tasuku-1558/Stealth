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

	void Initialize();				//初期化処理
	void Activate();				//活性化処理
	void Update(float deltaTime);	//更新処理
	void Draw();					//描画処理

private:
	FireWorksParticle(const FireWorksParticle&);	//コピーコンストラクタ

	unsigned int color;		//パーティクルの色
};