#pragma once


/// <summary>
/// デルタタイムクラス
/// </summary>
class DeltaTime final
{
public:
	DeltaTime();
	virtual ~DeltaTime();

	static void Initialize();
	static void DeltaTimeCount();

	static const float GetDeltaTime() { return deltaTime; }


private:

	static float deltaTime;
	static float nowTime;
	static float prevTime;
};