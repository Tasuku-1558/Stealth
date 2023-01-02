#include "HitChecker.h"
#include "Player.h"
#include "Ball.h"
#include "Map.h"
#include "PreCompiledHeader.h"
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

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="player"></param>
/// <param name="ball"></param>
void HitChecker::Check(Player* player, Ball* ball, Map* map)
{
	BallAndPlayer(player, ball);
	MapAndPlayer(map);
}

/// <summary>
/// ボールとプレイヤーの当たり判定
/// </summary>
/// <param name="player"></param>
/// <param name="ball"></param>
void HitChecker::BallAndPlayer(Player* player, Ball* ball)
{
	//プレイヤーからボールの座標を引いた値を取得
	double posX = player->GetPosition().x - ball->GetPosition().x;
	double posZ = player->GetPosition().z - ball->GetPosition().z;

	//プレイヤーとボールの2点間の距離を計算
	direction = sqrt(pow(posX, 2) + pow(posZ, 2));
	
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

void HitChecker::MapAndPlayer(Map* map)
{
}