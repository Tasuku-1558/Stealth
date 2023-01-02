#pragma once

#include "DxLib.h"

class Player;
class Ball;
class Map;


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


private:

	HitChecker(const HitChecker&);		//コピーコンストラクタ

	void BallAndPlayer(Player* player, Ball* ball);			//ボールとプレイヤーの当たり判定
	void MapAndPlayer(Map* map);

	double direction;
	bool hit;				//衝突したならば
	bool possessionBoal;	//所持しているボールの数

};