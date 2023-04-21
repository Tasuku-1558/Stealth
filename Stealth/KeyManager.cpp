#include "KeyManager.h"
#include "DxLib.h"
#include <chrono>


/// <summary>
/// �R���X�g���N�^
/// </summary>
KeyManager::KeyManager()
    : keyReleaseCount(0)
    , currentKeyState()
    , prevKeyState()
    , KEY_NUMBER(256)
    , INITIAL_RELEASE_COUNT(0)
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
/// <returns>keyManager��Ԃ�</returns>
KeyManager& KeyManager::GetInstance()
{
	static KeyManager keyManager;
	return keyManager;
}

/// <summary>
/// �X�V����
/// </summary>
void KeyManager::Update()
{
    for (int i = 0; i < KEY_NUMBER; ++i)
    {
        prevKeyState[i] = currentKeyState[i];  //prev���X�V
    }

    //�L�[�̉�����Ԃ��擾
    GetHitKeyStateAll(currentKeyState);

    //�����L�[��������Ă�����J�E���g�����Z�b�g
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
/// �L�[��������Ă��邩
/// </summary>
/// <param name="keyCode">�L�[�̎��</param>
/// <returns>�L�[��������Ă��邩�ǂ�����Ԃ�</returns>
bool KeyManager::CheckPressed(int keyCode) const
{
    if (currentKeyState[keyCode] == 0)
    {
        return false;   //���t���[���ŉ�����Ă��Ȃ�
    }

    return true;        //���t���[���ŉ�����Ă���
}