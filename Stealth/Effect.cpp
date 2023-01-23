#include "Effect.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"


const string Effect::EFFECT_FOLDER_PATH = "data/effect/";		//effectフォルダまでのパス
const string Effect::BALL_PATH			= "ball.efkefc";		//ボール再スポーン時エフェクトのパス

/// <summary>
/// コンストラクタ
/// </summary>
Effect::Effect() : EffectBase()
	, effectHandle(0)
	, effectPos_X(0.0f)
	, effectPos_Y(0.0f)
	, effectPos_Z(0.0f)
	, effectTime(0)
	, playingEffectHandle(0)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Effect::~Effect()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Effect::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + BALL_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 30.0f);
}

/// <summary>
/// 終了処理
/// </summary>
void Effect::Finalize()
{
	//エフェクトリソースを削除
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// 活性化処理
/// </summary>
void Effect::Activate()
{
	//エフェクトを停止する
	StopEffekseer3DEffect(playingEffectHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="ballPosX"></param>
/// <param name="ballPosY"></param>
/// <param name="ballPosZ"></param>
void Effect::Update(float ballPosX, float ballPosY, float ballPosZ)
{
	//エフェクトの位置設定
	effectPos_X = ballPosX;
	effectPos_Y = ballPosY;
	effectPos_Z = ballPosZ;

	//定期的にエフェクトを再生
	if (effectTime % 1 == 0)
	{
		//エフェクトを再生
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	//再生中のエフェクトを移動
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, effectPos_Z);

	//時間を経過
	effectTime++;
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