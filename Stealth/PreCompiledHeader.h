#pragma once

#include "DxLib.h"

const bool IS_WINDOW_MODE = true;					//ウィンドウモードにするかしないか

const int  SCREEN_WIDTH   = 1920;					//ウィンドウの幅
const int  SCREEN_HEIGHT  = 1080;					//ウィンドウの高さ
const int  COLOR_BIT      = 32;                     //カラービット数

const int MAX_PARTICLE_NUMBER = 2200;               //画面に表示する最大パーティクル数

const VECTOR ZERO_VECTOR  = { 0.0f, 0.0f, 0.0f };	//ゼロベクトル

////シャドウマップのサイズ
//const int  SHADOWMAP_SIZE_X = 1920;
//const int  SHADOWMAP_SIZE_Y = 1080;

//const VECTOR LIGHT_DIRECTION       = { 0.01f, -0.5f, 0.01f };         //シャドウマップが想定するライトの方向
//const VECTOR SHADOWMAP_MINPOSITION = { -3000.0f, -1.0f, -3000.0f }; //影を描画する範囲の座標の最小値
//const VECTOR SHADOUMAP_MAXPOSITION = { 3000.0f, 3000.0f, 3000.0f }; //影を描画する範囲の座標の最大値