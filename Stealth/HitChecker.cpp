#include "HitChecker.h"
#include "PreCompiledHeader.h"

#include "Player.h"
#include "Enemy.h"
#include "Cake.h"
#include "GoalFlag.h"

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
HitChecker::HitChecker()
	: hitPolyDim()
	, uiPosition()
	, uiHit(false)
	, pushBack()
	, mapHit(false)
	, flagHit(false)
	, UI_POSITION({ 0.0f, 30.0f, 800.0f })
{
	uiPosition = UI_POSITION;
}

/// <summary>
/// デストラクタ
/// </summary>
HitChecker::~HitChecker()
{
	//処理なし
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="model"></param>
/// <param name="player"></param>
void HitChecker::Check(int model, Player* player, vector<Cake*>* cake, /*vector<Enemy*>* enemy,*/ GoalFlag* goalFlag)
{
	CakeAndPlayer(player, cake);
	//EnemyAndPlayer(player, enemy);
	PlayerAndUI(player);
	MapAndPlayer(model, player);
	FlagAndPlayer(goalFlag, player);
}

/// <summary>
/// ケーキとプレイヤーの当たり判定
/// </summary>
/// <param name="player"></param>
/// <param name="cake"></param>
void HitChecker::CakeAndPlayer(Player* player, vector<Cake*>* cake)
{
	for (auto itr = cake->begin(); itr != cake->end(); ++itr)
	{
		//プレイヤーからケーキの座標を引いた値を取得
		VECTOR sub = player->GetPosition() - (*itr)->GetPosition();

		//プレイヤーとケーキの距離を計算
		float direction = VSize(sub);
		float radius = player->GetCollide().radius + (*itr)->GetCollideRadius();

		//衝突しているならば
		if (direction <= radius)
		{
			//ケーキの反応
			(*itr)->HitCake();
		}
	}
}

/// <summary>
/// エネミーとプレイヤーの当たり判定
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
void HitChecker::EnemyAndPlayer(Player* player, /*vector<Enemy*>* enemy*/Enemy* enemy)
{
	//for (auto itr = enemy->begin(); itr != enemy->end(); ++itr)
	{
		//プレイヤーからエネミーの座標を引いた値を取得
		VECTOR sub = player->GetPosition() - /*(*itr)*/enemy->GetPosition();

		//プレイヤーとエネミーの距離を計算
		float direction = VSize(sub);
		float radius = player->GetCollide().radius + /*(*itr)*/enemy->GetCollideRadius();

		//衝突しているならば
		if (direction <= radius)
		{
			//エネミーの反応
			/*(*itr)*/enemy->HitPlayer();
		}
	}
}

/// <summary>
/// プレイヤーとUI画像の当たり判定
/// </summary>
/// <param name="player"></param>
void HitChecker::PlayerAndUI(Player* player)
{
	//プレイヤーからUI画像の座標を引いた値を取得
	VECTOR sub = player->GetPosition() - uiPosition;

	//プレイヤーとUI画像の距離を計算
	float direction = VSize(sub);
	float radius = player->GetCollide().radius + 50.0f;

	//衝突しているならば
	if (direction <= radius)
	{
		uiHit = true;
	}
	else
	{
		uiHit = false;
	}
}

/// <summary>
/// マップとプレイヤーの当たり判定
/// </summary>
/// <param name="model"></param>
/// <param name="player"></param>
void HitChecker::MapAndPlayer(int model, Player* player)
{
	//モデル全体のコリジョン情報を構築
	MV1SetupCollInfo(model, 0, 8, 8, 8);

	//マップモデルとプレイヤーの当たり判定
	hitPolyDim = MV1CollCheck_Sphere(model, -1, player->GetCollide().worldCenter, player->GetCollide().radius);

	VECTOR moveCandidate = player->GetCollide().worldCenter;	//球中心候補
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);					//移動ベクトル
	VECTOR planeNormal = VGet(0.0f, 0.0f, 0.0f);				//ポリゴン平面法線
	VECTOR newCenter = player->GetCollide().worldCenter;		//移動候補
	float  moveLengh = 0.0f;									//移動量

	//プレイヤーがマップに当たったかどうか
	if (hitPolyDim.HitNum)
	{	
		mapHit = true;

		//衝突ポリゴンをすべて回って、球のめり込みを解消
		for (int i = 0; i < hitPolyDim.HitNum; ++i)
		{
			//衝突ポリゴンの辺 
			VECTOR edge1 = hitPolyDim.Dim[i].Position[1] - hitPolyDim.Dim[i].Position[0];
			VECTOR edge2 = hitPolyDim.Dim[i].Position[2] - hitPolyDim.Dim[i].Position[0];

			//衝突ポリゴンの辺より、ポリゴン面の法線ベクトルを求める
			planeNormal = VCross(edge1, edge2);
			planeNormal = VNorm(planeNormal);

			//プレイヤー中心に最も近いポリゴン平面の点を求める
			VECTOR tmp = moveCandidate - hitPolyDim.Dim[i].Position[0];
			float  dot = VDot(planeNormal, tmp);

			//衝突点
			VECTOR hitPos = moveCandidate - planeNormal * dot;

			//プレイヤーがどれくらいめり込んでいるかを算出
			VECTOR tmp2 = moveCandidate - hitPos;
			float  len = VSize(tmp2);

			//めり込んでいる場合はプレイヤーの中心を押し戻し
			if (HitCheck_Sphere_Triangle(moveCandidate, player->GetCollide().radius,
				hitPolyDim.Dim[i].Position[0],
				hitPolyDim.Dim[i].Position[1],
				hitPolyDim.Dim[i].Position[2]))
			{
				//めり込み解消する位置まで移動
				VECTOR moveVec;
				len = player->GetCollide().radius - len;
				moveVec = planeNormal * len;
				moveCandidate += moveVec;
			}

			//移動候補を移動位置にする
			newCenter = moveCandidate;

			pushBack = newCenter - player->GetDirection() + VScale(player->GetDirection(), 10.0f);
		}
	}
	else
	{
		mapHit = false;
	}
}

/// <summary>
/// ゴールオブジェクトとプレイヤーの当たり判定
/// </summary>
/// <param name="goalFlag"></param>
/// <param name="player"></param>
void HitChecker::FlagAndPlayer(GoalFlag* goalFlag, Player* player)
{
	//プレイヤーからゴール旗の座標を引いた値を取得
	VECTOR sub = player->GetPosition() - goalFlag->GetPosition();

	//プレイヤーとゴール旗の距離を計算
	float direction = VSize(sub);

	float radius = player->GetCollide().radius + goalFlag->GetCollideRadius();

	//衝突しているならば
	if (direction <= radius)
	{
		flagHit = true;
	}
	else
	{
		flagHit = false;
	}
}