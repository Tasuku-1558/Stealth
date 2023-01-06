#include "HitChecker.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Map.h"
#include "Wall.h"
#include "PreCompiledHeader.h"


using namespace Math3d;

HitChecker::HitChecker()
	: direction(0.0f)
	, hit(false)
	, hitPolyDim()
	, a()
	, aio(false)
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
	MV1SetupCollInfo(map->GetModel(), 0, 8, 8, 8);

	// モデルと球との当たり判定
	hitPolyDim = MV1CollCheck_Sphere(map->GetModel(), -1, player->GetPosition(), 100.0f);

	VECTOR moveCandidate = player->GetPosition(); // 球中心候補 

	VECTOR moveVec = VGet(0, 0, 0);    // 移動ベクトル
	float  moveLen = 0.0f;           // 移動量
	VECTOR planeNormal;                    // ポリゴン平面法線

	VECTOR newCenter = player->GetPosition(); // 移動候補  
	
	aio = false;

	// 当たったかどうか
	if (hitPolyDim.HitNum)
	{
		printfDx("hit");

		aio = true;

		// 衝突ポリゴンをすべて回って、球のめり込みを解消
		for (int i = 0; i < hitPolyDim.HitNum; ++i)
		{
			// 衝突ポリゴンの辺 
			VECTOR edge1 = hitPolyDim.Dim[i].Position[1] - hitPolyDim.Dim[i].Position[0];
			VECTOR edge2 = hitPolyDim.Dim[i].Position[2] - hitPolyDim.Dim[i].Position[0];

			// 衝突ポリゴンの辺より、ポリゴン面の法線ベクトルを求める
			planeNormal = VCross(edge1, edge2);
			planeNormal = VNorm(planeNormal);

			// 球中心に最も近いポリゴン平面の点を求める
			VECTOR tmp = moveCandidate - hitPolyDim.Dim[i].Position[0];
			float  dot = VDot(planeNormal, tmp);

			// 衝突点
			VECTOR hitPos = moveCandidate - planeNormal * dot;

			// 球がどれくらいめり込んでいるかを算出
			VECTOR tmp2 = moveCandidate - hitPos;
			float  len = VSize(tmp2);

			// めり込んでいる場合は球の中心を押し戻し
			if (HitCheck_Sphere_Triangle(moveCandidate, PLAYER_RADIUS,
				hitPolyDim.Dim[i].Position[0],
				hitPolyDim.Dim[i].Position[1],
				hitPolyDim.Dim[i].Position[2]))
			{
				// めり込み解消する位置まで移動
				VECTOR moveVec;
				len = PLAYER_RADIUS - len;
				moveVec = planeNormal * len;
				moveCandidate += moveVec;
			}

			// 移動候補を移動位置にする
			newCenter = moveCandidate;

			a = newCenter - player->GetPosition();

		}

	}
	
}

void HitChecker::WallAndEnemy(Wall* wall, Enemy* enemy)
{
}