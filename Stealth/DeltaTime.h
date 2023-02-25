#pragma once


/// <summary>
/// デルタタイムクラス
/// シングルトン
/// </summary>
class DeltaTime final
{
public:

	static DeltaTime& GetInstance();		//アドレスを返す

	void Initialize();						//初期化処理
	void DeltaTimeCount();					//60Fps計測

	//const float GetDeltaTime() { return deltaTime; }	//デルタタイムを返す

private:

	DeltaTime();
	DeltaTime(const DeltaTime&);			//コピーコンストラクタ
	virtual ~DeltaTime();

	//float deltaTime;		//前フレームと現在のフレームの差分
	//float waitFrameTime;	//待機フレーム時間(60fps)
	//LONGLONG nowTime;		//現在のフレーム
	//LONGLONG prevTime;		//昔のフレーム
};