#include "RepopEffect.h"
#include "EffekseerForDXLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="effectPath"></param>
/// <param name="effectSize"></param>
RepopEffect::RepopEffect(string effectPath, float effectSize)
{
	effectHandle = LoadEffekseerEffect(effectPath.c_str(), effectSize);
}

/// <summary>
/// デストラクタ
/// </summary>
RepopEffect::~RepopEffect()
{
	//エフェクトリソースを削除
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="position"></param>
void RepopEffect::Update(VECTOR position)
{
	//時間を経過
	effectTime++;

	//エフェクトを再生
	if (effectTime % 1 == 0)
	{
		//エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		effectTime = 0;
	}

	//再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}

/// <summary>
/// 描画処理
/// </summary>
void RepopEffect::Draw()
{
	//再生中のエフェクトを更新
	UpdateEffekseer3D();

	//再生中のエフェクトを描画
	DrawEffekseer3D();
}