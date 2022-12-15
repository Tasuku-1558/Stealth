#include "HitChecker.h"
#include "Player.h"
#include "Boal.h"
#include "Common.h"
#include <math.h>


HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, possessionBoal(false)
{
	//処理なし
}

HitChecker::~HitChecker()
{
	//処理なし
}

//衝突判定
void HitChecker::Check(Player* player, Boal* boal)
{
	BoalAndPlayer(player, boal);
}

//ボールとプレイヤーの当たり判定
void HitChecker::BoalAndPlayer(Player* player, Boal* boal)
{
	
	//プレイヤーからボールの座標を引いた値を取得
	double posX = player->GetPosition().x - boal->GetPosition().x;
	double posZ = player->GetPosition().z - boal->GetPosition().z;

	//プレイヤーとボールの2点間の距離を計算
	direction = sqrt(pow(posX, 2) + pow(posZ, 2));
	
	//ボールを所持していないならば
	if (!possessionBoal)
	{
		if (direction < PLAYER_RADIUS + BOAL_RADIUS)
		{
			printfDx("hit");
			hit = true;
		}
		else
		{
			hit = false;
		}
	}
	
}