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

	void Check(Player* player, Boal* boal);
	bool Hit() { return hit; }

	//デバック用
	bool PossessionBoal() { return possessionBoal; }

private:

	HitChecker(const HitChecker&);		//コピーコンストラクタ

	void BoalAndPlayer(Player* player, Boal* boal);

	double direction;
	bool hit;				//衝突したならば
	bool possessionBoal;	//所持しているボールの数

};