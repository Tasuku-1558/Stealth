#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Ball;
class Map;
class Wall;
class Enemy;


/// <summary>
/// ヒットチェッカークラス
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();

	void Check(Player* player, Ball* ball, Map* map);			//衝突判定
	bool Hit() { return hit; }

	VECTOR ai() { return a; }
	bool hita() { return aio; }

private:

	HitChecker(const HitChecker&);		//コピーコンストラクタ

	void BallAndPlayer(Player* player, Ball* ball);			//ボールとプレイヤーの当たり判定
	void MapAndPlayer(Map* map, Player* player);
	void WallAndEnemy(Wall* wall, Enemy* enemy);

	double direction;
	bool hit;				//衝突したならば
	bool possessionBoal;	//所持しているボールの数

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;
	VECTOR a;
	bool aio;

};