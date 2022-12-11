#include "HitChecker.h"
#include "Player.h"
#include "Boal.h"


HitChecker::HitChecker()
	: HitPolyDim()
{
}

HitChecker::~HitChecker()
{
}

void HitChecker::Check(Player* player, Boal* boal)
{
	BoalAndPlayer(player,boal);
}

void HitChecker::BoalAndPlayer(Player* player, Boal* boal)
{
	HitPolyDim = MV1CollCheck_Sphere(player->GetModelHandle(), -1, boal->GetPosition(), 100.0f);

	if (HitPolyDim.HitNum >= 1)
	{
		printfDx("hit");
	}
}