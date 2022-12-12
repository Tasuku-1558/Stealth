#include "HitChecker.h"
#include "Player.h"
#include "Boal.h"


HitChecker::HitChecker()
	: hitPolyDim()
{
	//ˆ—‚È‚µ
}

HitChecker::~HitChecker()
{
	//ˆ—‚È‚µ
}

//Õ“Ë”»’è
void HitChecker::Check(Player* player, Boal* boal)
{
	BoalAndPlayer(player, boal);
}

void HitChecker::BoalAndPlayer(Player* player, Boal* boal)
{
	MV1SetupCollInfo(player->GetModelHandle(), -1, 8, 8, 8);
	hitPolyDim = MV1CollCheck_Sphere(player->GetModelHandle(), -1, boal->GetPosition(), 100.0f);

	if (hitPolyDim.HitNum >= 1)
	{
		printfDx("hit");
	}
}