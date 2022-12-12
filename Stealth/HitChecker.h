#pragma once

#include "DxLib.h"

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

private:

	HitChecker(const HitChecker&);		//コピーコンストラクタ

	void BoalAndPlayer(Player* player, Boal* boal);

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

};