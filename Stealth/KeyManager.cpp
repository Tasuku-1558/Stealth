#include "KeyManager.h"
#include "DxLib.h"
#include <chrono>


/// <summary>
/// コンストラクタ
/// </summary>
KeyManager::KeyManager()
    : keyReleaseCount(0)
    , currentKeyState()
    , prevKeyState()
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
KeyManager::~KeyManager()
{
    //処理なし
}

/// <summary>
/// アドレスを返す
/// </summary>
/// <returns>keyManagerを返す</returns>
KeyManager& KeyManager::GetInstance()
{
	static KeyManager keyManager;
	return keyManager;
}

/// <summary>
/// 更新処理
/// </summary>
void KeyManager::Update()
{
    for (int i = 0; i < 256; ++i)
    {
        prevKeyState[i] = currentKeyState[i];  //prevを更新
    }

    //キーの押下状態を取得
    GetHitKeyStateAll(currentKeyState);

    //何かキーが押されていたらカウントリセット
    for (int i = 0; i < 256; ++i)
    {
        if (currentKeyState[i])
        {
            keyReleaseCount = 0;
            return;
        }
    }

    ++keyReleaseCount;
}

/// <summary>
/// キーが押されているか
/// </summary>
/// <param name="keyCode">キーの種類</param>
/// <returns>キーが押されているかどうかを返す</returns>
bool KeyManager::CheckPressed(int keyCode) const
{
    if (currentKeyState[keyCode] == 0)
    {
        return false;   //現フレームで押されていない
    }

    return true;        //現フレームで押されている
}