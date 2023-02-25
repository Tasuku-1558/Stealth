#include "DeltaTime.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
DeltaTime::DeltaTime()
	//: deltaTime(0.0f)
	//, waitFrameTime(0.0f)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
DeltaTime::~DeltaTime()
{
	//処理なし
}

/// <summary>
/// アドレスを返す
/// </summary>
/// <returns></returns>
DeltaTime& DeltaTime::GetInstance()
{
	static DeltaTime deltaTime;
	return deltaTime;
}

/// <summary>
/// 初期化処理
/// </summary>
void DeltaTime::Initialize()
{
	//時間計測
	//prevTime = nowTime = GetNowHiPerformanceCount();

	////待機フレーム時間(60fps)
	//waitFrameTime = 16667.0f;
}

/// <summary>
/// 60Fps計測
/// </summary>
void DeltaTime::DeltaTimeCount()
{
	//現在のフレームを更新
	//nowTime = GetNowHiPerformanceCount();

	//deltaTime = (nowTime - prevTime) / 1000000.0f;

	////60fps制御用ループ
	//while (GetNowHiPerformanceCount() - nowTime < waitFrameTime);

	////現在のフレームを保存
	//prevTime = nowTime;
}