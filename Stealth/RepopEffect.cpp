#include "RepopEffect.h"
#include "EffekseerForDXLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
RepopEffect::RepopEffect(/*string effectPath, float effectSize*/)
	: EffectBase()
	, EFFECT_FOLDER_PATH("Data/effect/")
	, CAKE_PATH("cake.efkefc")
	, MAGNIFICATION(30.0f)
{
	string failePath = EFFECT_FOLDER_PATH + CAKE_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), MAGNIFICATION);
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
/// <param name="pos"></param>
void RepopEffect::Update(VECTOR pos)
{
	//定期的にエフェクトを再生
	if (effectTime % 1 == 0)
	{
		//エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	//再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y, pos.z);

	//時間を経過
	effectTime++;
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