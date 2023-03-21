#include "KeyManager.h"
#include "DxLib.h"
#include <chrono>


/// <summary>
/// �R���X�g���N�^
/// </summary>
KeyManager::KeyManager()
    : currentKeyState()
    , prevKeyState()
    , keyReleaseCount(0)
{
    //�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
KeyManager::~KeyManager()
{
    //�����Ȃ�
}

/// <summary>
/// �A�h���X��Ԃ�
/// </summary>
/// <returns></returns>
KeyManager& KeyManager::GetInstance()
{
	static KeyManager keyManger;
	return keyManger;
}

/// <summary>
/// �X�V����
/// </summary>
void KeyManager::Update()
{
    for (int i = 0; i < 256; ++i)
    {
        prevKeyState[i] = currentKeyState[i];  //prev���X�V
    }

    //�L�[�̉�����Ԃ��擾
    GetHitKeyStateAll(currentKeyState);

    //�����L�[��������Ă�����J�E���g���Z�b�g
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
/// �L�[��������Ă��邩
/// </summary>
/// <param name="keyCode"></param>
/// <returns></returns>
bool KeyManager::CheckPressed(int keyCode) const
{
    if (currentKeyState[keyCode] == 0)
    {
        return false;   //���t���[���ŉ�����Ă��Ȃ�
    }

    return true;        //���t���[���ŉ�����Ă���
}