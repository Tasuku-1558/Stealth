#pragma once

class Player;
class Boal;


/// <summary>
/// ヒットチェッカークラス
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();

	void Check(Player* player, Boal* boal);			//衝突判定
	bool Hit() { return hit; }


private:

	HitChecker(const HitChecker&);		//コピーコンストラクタ

	void BoalAndPlayer(Player* player, Boal* boal);			//ボールとプレイヤーの当たり判定
	void MapAndPlayer();

	double direction;
	bool hit;				//衝突したならば
	bool possessionBoal;	//所持しているボールの数

};