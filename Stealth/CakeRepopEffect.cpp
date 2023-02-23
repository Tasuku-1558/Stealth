#include "CakeRepopEffect.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"


//const string CakeRepopEffect::EFFECT_FOLDER_PATH = "data/effect/";		//effectフォルダまでのパス
//const string CakeRepopEffect::CAKE_PATH			 = "cake.efkefc";		//ケーキ再スポーン時エフェクトのパス


/// <summary>
/// コンストラクタ
/// </summary>
CakeRepopEffect::CakeRepopEffect() : EffectBase()
	, effectHandle(0)
	, effectPosX(0.0f)
	, effectPosY(0.0f)
	, effectPosZ(0.0f)
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
CakeRepopEffect::~CakeRepopEffect()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void CakeRepopEffect::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + CAKE_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 30.0f);
}

/// <summary>
/// 終了処理
/// </summary>
void CakeRepopEffect::Finalize()
{
	//エフェクトリソースを削除
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// 活性化処理
/// </summary>
void CakeRepopEffect::Activate()
{
	//エフェクトを停止する
	StopEffekseer3DEffect(playingEffectHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="cakePosX"></param>
/// <param name="cakePosY"></param>
/// <param name="cakePosZ"></param>
void CakeRepopEffect::Update(float cakePosX, float cakePosY, float cakePosZ)
{
	//エフェクトの位置設定
	effectPosX = cakePosX;
	effectPosY = cakePosY;
	effectPosZ = cakePosZ;

	//定期的にエフェクトを再生
	if (effectTime % 1 == 0)
	{
		//エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	//再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPosX, effectPosY, effectPosZ);

	//時間を経過
	effectTime++;
}

/// <summary>
/// 描画処理
/// </summary>
void CakeRepopEffect::Draw()
{
	//再生中のエフェクトを更新
	UpdateEffekseer3D();

	//再生中のエフェクトを描画
	DrawEffekseer3D();
}