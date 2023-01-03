#include "HitChecker.h"
#include "Player.h"
#include "Ball.h"
#include "Map.h"
#include "PreCompiledHeader.h"


using namespace Math3d;

HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, possessionBoal(false)
	, HitPolyDim()
	, a(false)
{
	//処理なし
}

HitChecker::~HitChecker()
{
	//処理なし
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="player"></param>
/// <param name="ball"></param>
void HitChecker::Check(Player* player, Ball* ball, Map* map)
{
	BallAndPlayer(player, ball);
	MapAndPlayer(map, player);
}

/// <summary>
/// ボールとプレイヤーの当たり判定
/// </summary>
/// <param name="player"></param>
/// <param name="ball"></param>
void HitChecker::BallAndPlayer(Player* player, Ball* ball)
{
	//プレイヤーからボールの座標を引いた値を取得
	VECTOR sub = player->GetPosition() - ball->GetPosition();

	//プレイヤーとエネミーの2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));
	
	//ボールを所持していないならば
	//if (!possessionBoal)
	{
		if (direction < PLAYER_RADIUS + BALL_RADIUS)
		{
			hit = true;
		}
		else
		{
			hit = false;
		}
	}
	
}

void HitChecker::MapAndPlayer(Map* map, Player* player)
{

	// モデル全体のコリジョン情報を構築
	MV1SetupCollInfo(map->GetModel(), -1, 8, 8, 8);

	// モデルと球との当たり判定
	HitPolyDim = MV1CollCheck_Sphere(map->GetModel(), -1, player->GetPosition(), 100.0f);

	// 当たったかどうかで処理を分岐
	if (HitPolyDim.HitNum >= 1)
	{

		printfDx("hit");
		a = true;
		HitPolyDim.HitNum = 0;
	}
	else
	{
		a = false;
	}
}