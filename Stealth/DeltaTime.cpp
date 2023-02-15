#include "DeltaTime.h"
#include "DxLib.h"


float DeltaTime::deltaTime = 0.0f;
float DeltaTime::prevTime  = 0.0f;
float DeltaTime::nowTime   = 0.0f;

/// <summary>
/// コンストラクタ
/// </summary>
DeltaTime::DeltaTime()
{
}

/// <summary>
/// デストラクタ
/// </summary>
DeltaTime::~DeltaTime()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void DeltaTime::Initialize()
{
	// 時間計測
	prevTime = nowTime = GetNowCount();
}

void DeltaTime::DeltaTimeCount()
{
	// フレーム時間を算出
	nowTime = GetNowCount();

	deltaTime = (nowTime - prevTime) / 1000.0f;

	prevTime = nowTime;
}