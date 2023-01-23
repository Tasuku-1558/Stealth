#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Wall;
class Ball;


/// <summary>
/// ヒットチェッカークラス
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	 virtual ~HitChecker();

	void Check(int model, Player* player);							//衝突判定
	void BallAndPlayer(VECTOR playerPos, Ball* ball);			//ボールとプレイヤーの当たり判定


	bool UI() { return uiDraw; }
	VECTOR Back() { return pushBack; }								//マップの壁にプレイヤーが衝突したときの押し戻し値を返す
	bool MapHit() { return mapHit; }								//マップもプレイヤーが衝突したならば

private:

	HitChecker(const HitChecker&);							//コピーコンストラクタ

	void PlayerAndUI(Player* player);						//プレイヤーとUI画像の当たり判定
	void MapAndPlayer(int model, Player* player);


	bool ballHit;			//ボールに衝突したならば
	VECTOR uiPos;			//UI画像の位置
	bool uiDraw;			//UI画像を描画するかどうか

	bool mapHit;			//マップモデルに衝突したならば
	VECTOR pushBack;

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};