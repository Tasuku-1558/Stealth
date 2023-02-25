#include "RepopEffect.h"
#include "EffekseerForDXLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
RepopEffect::RepopEffect() : EffectBase()
	, effectHandle(0)
	, effectTime(0)
	, playingEffectHandle(0)
	, EFFECT_FOLDER_PATH("data/effect/")
	, CAKE_PATH("cake.efkefc")
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
RepopEffect::~RepopEffect()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void RepopEffect::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + CAKE_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 30.0f);
}

/// <summary>
/// 終了処理
/// </summary>
void RepopEffect::Finalize()
{
	//エフェクトリソースを削除
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// 活性化処理
/// </summary>
void RepopEffect::Activate()
{
	//エフェクトを停止する
	StopEffekseer3DEffect(playingEffectHandle);
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