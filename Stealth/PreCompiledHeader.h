#pragma once

#include "DxLib.h"

//-----------------------------------------------------------------------------
// 共通の定数などの宣言
//-----------------------------------------------------------------------------
const bool IS_WINDOW_MODE = true;					//ウィンドウモードにするか

const int  SCREEN_WIDTH  = 1920;					//ウィンドウの幅
const int  SCREEN_HEIGHT = 1080;					//ウィンドウの高さ

const VECTOR ZERO_VECTOR = { 0.0f, 0.0f, 0.0f };	//ゼロベクトル

const float PLAYER_RADIUS = 100.0f;                 //プレイヤーの半径
const float BOAL_RADIUS   = 50.0f;                  //ボールの半径


// インスタンスをdeleteしてNULLを入れる
template <typename T>
inline void SafeDelete(T*& p)
{
    delete (p);
    (p) = nullptr;
}