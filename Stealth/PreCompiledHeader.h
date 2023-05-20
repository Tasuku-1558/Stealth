#pragma once

#include "DxLib.h"

const int  SCREEN_WIDTH   = 1920;					//�E�B���h�E�̕�
const int  SCREEN_HEIGHT  = 1080;					//�E�B���h�E�̍���
const int  COLOR_BIT      = 32;                     //�J���[�r�b�g��

const int MAX_PARTICLE_NUMBER = 2200;               //��ʂɕ\������ő�p�[�e�B�N����

const int BLOCK_NUM_X = 16;							//�u���b�N��X�T�C�Y
const int BLOCK_NUM_Z = 16;							//�u���b�N��Z�T�C�Y

const float WAIT_FRAME_TIME = 16667.0f;				//�ҋ@�t���[������(60fps)
const float NOMAL_DELETA_TIME_DIVISION = 1000000.0f;//�ʏ펞�̃f���^�^�C��������l

const float PI = DX_PI_F / 180.0f;

const bool IS_WINDOW_MODE = true;					//�E�B���h�E���[�h�ɂ��邩���Ȃ���

const VECTOR ZERO_VECTOR  = { 0.0f, 0.0f, 0.0f };	//�[���x�N�g��

////�V���h�E�}�b�v�̃T�C�Y
//const int  SHADOWMAP_SIZE_X = 1920;
//const int  SHADOWMAP_SIZE_Y = 1080;

//const VECTOR LIGHT_DIRECTION       = { 0.01f, -0.5f, 0.01f };         //�V���h�E�}�b�v���z�肷�郉�C�g�̕���
//const VECTOR SHADOWMAP_MINPOSITION = { -3000.0f, -1.0f, -3000.0f }; //�e��`�悷��͈͂̍��W�̍ŏ��l
//const VECTOR SHADOUMAP_MAXPOSITION = { 3000.0f, 3000.0f, 3000.0f }; //�e��`�悷��͈͂̍��W�̍ő�l