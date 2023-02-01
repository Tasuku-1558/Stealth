#pragma once

#include "DxLib.h"

//-----------------------------------------------------------------------------
// ���ʂ̒萔�Ȃǂ̐錾
//-----------------------------------------------------------------------------
const bool IS_WINDOW_MODE = true;					//�E�B���h�E���[�h�ɂ��邩

const int  SCREEN_WIDTH   = 1920;					//�E�B���h�E�̕�
const int  SCREEN_HEIGHT  = 1080;					//�E�B���h�E�̍���

const VECTOR ZERO_VECTOR  = { 0.0f, 0.0f, 0.0f };	//�[���x�N�g��

const float PLAYER_RADIUS = 100.0f;                 //�v���C���[�̔��a
const float ENEMY_RADIUS  = 100.0f;                 //�G�l�~�[�̔��a
const float CAKE_RADIUS   = 50.0f;                  //�P�[�L�̔��a
const float BULLET_RADIUS = 50.0f;                  //�o���b�g�̔��a

////�V���h�E�}�b�v�̃T�C�Y
//const int  SHADOWMAP_SIZE_X = 1920;
//const int  SHADOWMAP_SIZE_Y = 1080;
//
//const VECTOR LIGHT_DIRECTION       = { 0.01f, -0.5f, 0.01f };         //�V���h�E�}�b�v���z�肷�郉�C�g�̕���
//const VECTOR SHADOWMAP_MINPOSITION = { -3000.0f, -1.0f, -3000.0f }; //�e��`�悷��͈͂̍��W�̍ŏ��l
//const VECTOR SHADOUMAP_MAXPOSITION = { 3000.0f, 3000.0f, 3000.0f }; //�e��`�悷��͈͂̍��W�̍ő�l


//�C���X�^���X��delete����NULL������
template <typename T>
inline void SafeDelete(T*& p)
{
    delete (p);
    (p) = nullptr;
}