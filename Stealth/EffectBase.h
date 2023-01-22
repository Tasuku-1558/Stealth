#pragma once


/// <summary>
/// エフェクトベースクラス
/// </summary>
class EffectBase
{
public:
	EffectBase() {/*処理なし*/ };
	virtual ~EffectBase() {/*処理なし*/ };

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate() = 0;
	virtual void Update(float ballPosX, float ballPosY, float ballPosZ) = 0;
	virtual void Draw() = 0;

private:
	EffectBase(const EffectBase&);		//コピーコンストラクタ
};