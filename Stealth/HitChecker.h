#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Wall;


/// <summary>
/// ヒットチェッカークラス
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	 virtual ~HitChecker();

	void Check(int model, Player* player);							//衝突判定
	void BallAndPlayer(VECTOR playerPos, VECTOR ballPos);			//ボールとプレイヤーの当たり判定


	bool Hit() { return hit; }
	bool UI() { return uiDraw; }

	bool MapHit() { return mapHit; }

private:

	HitChecker(const HitChecker&);		//コピーコンストラクタ

	void PlayerAndUI(Player* player);						//プレイヤーとUI画像の当たり判定
	void MapAndPlayer(int model, Player* player);


	bool hit;				//衝突したならば
	VECTOR uiPos;
	bool uiDraw;

	bool mapHit;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};