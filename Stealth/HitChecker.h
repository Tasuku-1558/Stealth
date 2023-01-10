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

	void Check(Player* player, Ball* ball, Map* map, Enemy* enemy);			//衝突判定
	bool Hit() { return hit; }
	bool UI() { return uiDraw; }

private:

	HitChecker(const HitChecker&);		//コピーコンストラクタ

	void BallAndPlayer(Player* player, Ball* ball);			//ボールとプレイヤーの当たり判定
	void PlayerAndUI(Player* player);
	void MapAndPlayer(Map* map, Player* player);
	void WallAndEnemy(Wall* wall, Enemy* enemy);
	void BulletAndEnemy(Player* player, Enemy* enemy);

	bool hit;				//衝突したならば
	VECTOR uiPos;
	bool uiDraw;

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};