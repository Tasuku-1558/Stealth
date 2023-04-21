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
    , KEY_NUMBER(256)
    , INITIAL_RELEASE_COUNT(0)
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
    for (int i = 0; i < KEY_NUMBER; ++i)
    {
        prevKeyState[i] = currentKeyState[i];  //prevを更新
    }

    //キーの押下状態を取得
    GetHitKeyStateAll(currentKeyState);

    //何かキーが押されていたらカウントをリセット
    for (int i = 0; i < KEY_NUMBER; ++i)
    {
        if (currentKeyState[i])
        {
            keyReleaseCount = INITIAL_RELEASE_COUNT;
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