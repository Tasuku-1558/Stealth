#pragma once

#include "DxLib.h"

//-----------------------------------------------------------------------------
// 共通の定数などの宣言
//-----------------------------------------------------------------------------
const bool IS_WINDOW_MODE = true;					//ウィンドウモードにするか

const int  SCREEN_WIDTH   = 1920;					//ウィンドウの幅
const int  SCREEN_HEIGHT  = 1080;					//ウィンドウの高さ

const VECTOR ZERO_VECTOR  = { 0.0f, 0.0f, 0.0f };	//ゼロベクトル

const float PLAYER_RADIUS = 100.0f;                 //プレイヤーの半径
const float ENEMY_RADIUS  = 100.0f;                 //エネミーの半径
const float CAKE_RADIUS   = 50.0f;                  //ケーキの半径
const float BULLET_RADIUS = 50.0f;                  //バレットの半径

////シャドウマップのサイズ
//const int  SHADOWMAP_SIZE_X = 1920;
//const int  SHADOWMAP_SIZE_Y = 1080;
//
//const VECTOR LIGHT_DIRECTION       = { 0.01f, -0.5f, 0.01f };         //シャドウマップが想定するライトの方向
//const VECTOR SHADOWMAP_MINPOSITION = { -3000.0f, -1.0f, -3000.0f }; //影を描画する範囲の座標の最小値
//const VECTOR SHADOUMAP_MAXPOSITION = { 3000.0f, 3000.0f, 3000.0f }; //影を描画する範囲の座標の最大値


//インスタンスをdeleteしてNULLを入れる
template <typename T>
inline void SafeDelete(T*& p)
{
    delete (p);
    (p) = nullptr;
}