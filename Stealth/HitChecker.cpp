#include "HitChecker.h"
#include "PreCompiledHeader.h"

#include "Player.h"
#include "Cake.h"


using namespace Math3d;

/// <summary>
/// コンストラクタ
/// </summary>
HitChecker::HitChecker()
	: cakeHit(false)
	, hitPolyDim()
	, uiPosition()
	, uiDraw(false)
	, pushBack()
	, mapHit(false)
	, enemyHit(false)
	, UI_POSITION({ -800.0f, 30.0f, 0.0f })
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
void HitChecker::Check(int model, Player* player, VECTOR flagPos)
{
	PlayerAndUI(player);
	MapAndPlayer(model, player);
	FlagAndPlayer(flagPos, player);
}

/// <summary>
/// ケーキとプレイヤーの当たり判定
/// </summary>
/// <param name="playerPos"></param>
/// <param name="cake"></param>
void HitChecker::CakeAndPlayer(VECTOR playerPos, Cake* cake)
{
	//プレイヤーからケーキの座標を引いた値を取得
	VECTOR sub = playerPos - cake->GetPosition();

	//プレイヤーとケーキの2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));
	
	//衝突しているならば
	if (direction < PLAYER_RADIUS + CAKE_RADIUS)
	{
		cakeHit = true;
	}
	else
	{
		cakeHit = false;
	}
}

/// <summary>
/// エネミーとプレイヤーの当たり判定
/// </summary>
/// <param name="playerPos"></param>
/// <param name="monitoringEnemy"></param>
void HitChecker::EnemyAndPlayer(VECTOR playerPos, VECTOR enemyPos)
{
	//プレイヤーからケーキの座標を引いた値を取得
	VECTOR sub = playerPos - enemyPos;

	//プレイヤーとケーキの2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//衝突しているならば
	if (direction < PLAYER_RADIUS + ENEMY_RADIUS)
	{
		enemyHit = true;
	}
	else
	{
		enemyHit = false;
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

	//プレイヤーとUI画像の2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//衝突しているならば
	if (direction < PLAYER_RADIUS + 50.0f)
	{
		uiDraw = true;
	}
	else
	{
		uiDraw = false;
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
	hitPolyDim = MV1CollCheck_Sphere(model, -1, player->GetPosition(), 100.0f);

	VECTOR moveCandidate = player->GetPosition(); //球中心候補

	VECTOR moveVec = VGet(0, 0, 0);    //移動ベクトル
	float  moveLengh = 0.0f;           //移動量
	VECTOR planeNormal = VGet(0, 0, 0);    //ポリゴン平面法線

	VECTOR newCenter = player->GetPosition(); //移動候補
	

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

			//球中心に最も近いポリゴン平面の点を求める
			VECTOR tmp = moveCandidate - hitPolyDim.Dim[i].Position[0];
			float  dot = VDot(planeNormal, tmp);

			//衝突点
			VECTOR hitPos = moveCandidate - planeNormal * dot;

			//球がどれくらいめり込んでいるかを算出
			VECTOR tmp2 = moveCandidate - hitPos;
			float  len = VSize(tmp2);

			//めり込んでいる場合は球の中心を押し戻し
			if (HitCheck_Sphere_Triangle(moveCandidate, PLAYER_RADIUS,
				hitPolyDim.Dim[i].Position[0],
				hitPolyDim.Dim[i].Position[1],
				hitPolyDim.Dim[i].Position[2]))
			{
				//めり込み解消する位置まで移動
				VECTOR moveVec;
				len = PLAYER_RADIUS - len;
				moveVec = planeNormal * len;
				moveCandidate += moveVec;
			}

			//移動候補を移動位置にする
			newCenter = moveCandidate;

			pushBack = newCenter - player->GetDir() + VScale(player->GetDir(), 10.0f);
		}
	}
	else
	{
		mapHit = false;
	}
}

/// <summary>
/// ゴール旗とプレイヤーの当たり判定
/// </summary>
/// <param name="flagPos"></param>
/// <param name="player"></param>
void HitChecker::FlagAndPlayer(VECTOR flagPos, Player* player)
{
	//プレイヤーからゴール旗の座標を引いた値を取得
	VECTOR sub = player->GetPosition() - flagPos;

	//プレイヤーとゴール旗の2点間の距離を計算
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//衝突しているならば
	if (direction < PLAYER_RADIUS + 50.0f)
	{
		flagHit = true;
	}
	else
	{
		flagHit = false;
	}
}