#include "Effect.h"
#include "EffekseerForDXLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="effectPath">エフェクトのパス</param>
/// <param name="effectSize">エフェクトのサイズ</param>
Effect::Effect(string effectPath, float effectSize)
{
	effectHandle = LoadEffekseerEffect(effectPath.c_str(), effectSize);
}

/// <summary>
/// デストラクタ
/// </summary>
Effect::~Effect()
{
	//エフェクトリソースを削除
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="position">エフェクトの位置</param>
void Effect::Update(VECTOR position)
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
void Effect::Draw()
{
	//再生中のエフェクトを更新
	UpdateEffekseer3D();

	//再生中のエフェクトを描画
	DrawEffekseer3D();
}