#pragma once

#include "DxLib.h"

//-----------------------------------------------------------------------------
// ���ʂ̒萔�Ȃǂ̐錾
//-----------------------------------------------------------------------------
const bool IS_WINDOW_MODE = true;					//�E�B���h�E���[�h�ɂ��邩

const int  SCREEN_WIDTH  = 1920;					//�E�B���h�E�̕�
const int  SCREEN_HEIGHT = 1080;					//�E�B���h�E�̍���

const VECTOR ZERO_VECTOR = { 0.0f, 0.0f, 0.0f };	//�[���x�N�g��

const float PLAYER_RADIUS = 100.0f;                 //�v���C���[�̔��a
const float BOAL_RADIUS   = 50.0f;                  //�{�[���̔��a


// �C���X�^���X��delete����NULL������
template <typename T>
inline void SafeDelete(T*& p)
{
    delete (p);
    (p) = nullptr;
}