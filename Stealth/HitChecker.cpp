#include "HitChecker.h"
#include "PreCompiledHeader.h"


using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
HitChecker::HitChecker()
	: moveLengh(0.0f)
	, uiHit(false)
	, flagHit(false)
	, uiPosition()
	, pushBack()
	, moveVec()
	, planeNormal()
	, hitPolyDim()
	, DIV_NUMBER(8)
	, FRAME_INDEX(-1)
	, RANGE_DEGREE(27.0f)
	, RANGE_HALF(2.0f)
	, LENGTH(900.0f)
	, SCALE(10.0f)
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
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
/// <param name="stageBlock">ステージブロックのポインタ</param>
/// <param name="player">プレイヤーのポインタ</param>
/// <param name="cakeBullet">ケーキバレットのポインタ</param>
/// <param name="enemy">エネミーのポインタ</param>
/// <param name="goalFlag">ゴールオブジェクトのポインタ</param>
void HitChecker::Check(float deltaTime, vector<StageBlock*>* stageBlock, Player* player, vector<CakeBullet*>* cakeBullet, vector<Enemy*>* enemy, GoalFlag* goalFlag)
{
	MapAndPlayer(stageBlock, player);
	CakeAndPlayer(player, cakeBullet);
	EnemyAndPlayer(player, enemy);
	PlayerAndUi(player);
	FlagAndPlayer(goalFlag, player);

	VisualAngleCake(deltaTime, enemy, cakeBullet);
	VisualAnglePlayer(player, enemy);
}

/// <summary>
/// ケーキとプレイヤーの当たり判定
/// </summary>
/// <param name="player">プレイヤーのポインタ</param>
/// <param name="cakeBullet">ケーキバレットのポインタ</param>
void HitChecker::CakeAndPlayer(Player* player, vector<CakeBullet*>* cakeBullet)
{
	for (auto itr = cakeBullet->begin(); itr != cakeBullet->end(); ++itr)
	{
		//プレイヤーからケーキの座標を引いた値を取得
		VECTOR sub = player->GetPosition() - (*itr)->cake->GetPosition();

		//プレイヤーとケーキの距離を計算
		float distance = VSize(sub);
		float radius = player->GetCollide().radius + (*itr)->cake->GetCollideRadius();

		//衝突しているならば
		if (distance <= radius)
		{
			//ケーキの反応
			(*itr)->cake->HitCake();
		}
	}
}

/// <summary>
/// エネミーとプレイヤーの当たり判定
/// </summary>
/// <param name="player">プレイヤーのポインタ</param>
/// <param name="enemy">エネミーのポインタ</param>
void HitChecker::EnemyAndPlayer(Player* player, vector<Enemy*>* enemy)
{
	for (auto itr = enemy->begin(); itr != enemy->end(); ++itr)
	{
		//プレイヤーからエネミーの座標を引いた値を取得
		VECTOR sub = player->GetPosition() - (*itr)->GetPosition();

		//プレイヤーとエネミーの距離を計算
		float distance = VSize(sub);
		float radius = player->GetCollide().radius + (*itr)->GetCollideRadius();

		//衝突しているならば
		if (distance <= radius)
		{
			//エネミーの反応
			(*itr)->HitPlayer();
		}
	}
}

/// <summary>
/// プレイヤーとUi画像の当たり判定
/// </summary>
/// <param name="player">プレイヤーのポインタ</param>
void HitChecker::PlayerAndUi(Player* player)
{
	//プレイヤーからUi画像の座標を引いた値を取得
	VECTOR sub = player->GetPosition() - uiPosition;

	//プレイヤーとUi画像の距離を計算
	float distance = VSize(sub);
	float radius = player->GetCollide().radius + 50.0f;

	//衝突しているならば
	if (distance <= radius)
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
/// <param name="stageBlock">ステージブロックのポインタ</param>
/// <param name="player">プレイヤーのポインタ</param>
void HitChecker::MapAndPlayer(vector<StageBlock*>* stageBlock, Player* player)
{
	for (auto itr = stageBlock->begin(); itr != stageBlock->end(); ++itr)
	{
		//モデル全体のコリジョン情報を構築
		MV1SetupCollInfo((*itr)->GetModelHandle(), FRAME_INDEX, DIV_NUMBER, DIV_NUMBER, DIV_NUMBER);

		//ステージモデルとプレイヤーの当たり判定
		hitPolyDim = MV1CollCheck_Sphere((*itr)->GetModelHandle(), FRAME_INDEX, player->GetCollide().worldCenter, player->GetCollide().radius);
		
		VECTOR moveCandidate;													//プレイヤー中心候補
		VECTOR newCenter = moveCandidate = player->GetCollide().worldCenter;	//移動候補

		//プレイヤーがマップに当たったかどうか
		if (hitPolyDim.HitNum)
		{

			//衝突ポリゴンをすべて回ってめり込みを解消
			for (int i = 0; i < hitPolyDim.HitNum; ++i)
			{
				//衝突ポリゴンの辺
				VECTOR edge1 = hitPolyDim.Dim[i].Position[1] - hitPolyDim.Dim[i].Position[0];
				VECTOR edge2 = hitPolyDim.Dim[i].Position[2] - hitPolyDim.Dim[i].Position[0];

				//衝突ポリゴンの辺より、ポリゴン面の法線ベクトルを求める
				planeNormal = VNorm(VCross(edge1, edge2));

				//プレイヤー中心に最も近いポリゴン平面の点を求める
				VECTOR tmp = moveCandidate - hitPolyDim.Dim[i].Position[0];
				float dot = VDot(planeNormal, tmp);

				//衝突点
				VECTOR hitPos = moveCandidate - planeNormal * dot;

				//プレイヤーがどれくらいめり込んでいるかを算出
				VECTOR tmp2 = moveCandidate - hitPos;
				float len = VSize(tmp2);

				//めり込んでいる場合はプレイヤーの中心を押し戻し
				if (HitCheck_Sphere_Triangle(moveCandidate, player->GetCollide().radius,
					hitPolyDim.Dim[i].Position[0],
					hitPolyDim.Dim[i].Position[1],
					hitPolyDim.Dim[i].Position[2]))
				{
					//めり込み解消する位置まで移動
					len = player->GetCollide().radius - len;
					moveVec = planeNormal * len;
					moveCandidate += moveVec;
				}

				//移動候補を移動位置にする
				newCenter = moveCandidate;

				pushBack = newCenter - player->GetDirection() + VScale(player->GetDirection(), SCALE);

				//プレイヤーの座標に押し戻し量を加える
				player->HitMap(pushBack);
			}
		}
	}
}

/// <summary>
/// ゴールオブジェクトとプレイヤーの当たり判定
/// </summary>
/// <param name="goalFlag">ゴールオブジェクトのポインタ</param>
/// <param name="player">プレイヤーのポインタ</param>
void HitChecker::FlagAndPlayer(GoalFlag* goalFlag, Player* player)
{
	//プレイヤーからゴール旗の座標を引いた値を取得
	VECTOR sub = player->GetPosition() - goalFlag->GetPosition();

	//プレイヤーとゴールオブジェクトの距離を計算
	float distance = VSize(sub);

	float radius = player->GetCollide().radius + goalFlag->GetCollideRadius();

	//衝突しているならば
	if (distance <= radius)
	{
		flagHit = true;
	}
}

/// <summary>
/// エネミーの視野にケーキが入った場合
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
/// <param name="enemy">エネミーのポインタ</param>
/// <param name="cakeBullet">ケーキバレットのポインタ</param>
void HitChecker::VisualAngleCake(float deltaTime, vector<Enemy*>* enemy, vector<CakeBullet*>* cakeBullet)
{
	for (auto itre = enemy->begin(); itre != enemy->end(); ++itre)
	{
		for (auto itr = cakeBullet->begin(); itr != cakeBullet->end(); ++itr)
		{
			//バレットからエネミーの座標を引いた値を取得
			VECTOR sub = (*itr)->bullet->GetPosition() - (*itre)->GetPosition();

			//バレットとエネミーの距離を計算
			float bulletDirection = VSize(sub);

			//ベクトルの正規化
			sub = VNorm(sub);

			//内積計算
			float dot = VDot(sub, (*itre)->GetDirection());

			float range = RANGE_DEGREE * PI;

			//エネミーの視野をcosにする
			float radian = cosf(range / RANGE_HALF);

			//ベクトルとエネミーの長さの比較
			if (LENGTH > bulletDirection)
			{
				//バレットがエネミーの視野範囲内にいるならば
				if (radian <= dot)
				{
					(*itre)->CakeFind(deltaTime, sub);

					if ((*itre)->CakeFlag())
					{
						break;
					}
				}
			}
			else
			{
				(*itre)->CakeReset();
			}
		}
	}
}

/// <summary>
/// エネミーの視野にプレイヤーが入った場合
/// </summary>
/// <param name="player">プレイヤーのポインタ</param>
/// <param name="enemy">エネミーのポインタ</param>
void HitChecker::VisualAnglePlayer(Player* player, vector<Enemy*>* enemy)
{
	for (auto itr = enemy->begin(); itr != enemy->end(); ++itr)
	{
		//プレイヤーからエネミーの座標を引いた値を取得
		VECTOR sub = player->GetPosition() - (*itr)->GetPosition();

		//プレイヤーとエネミーの距離を計算
		float playerDirection = VSize(sub);

		//ベクトルの正規化
		sub = VNorm(sub);

		//内積計算
		float dot = VDot(sub, (*itr)->GetDirection());

		float range = RANGE_DEGREE * PI;

		//エネミーの視野をcosにする
		float radian = cosf(range / RANGE_HALF);

		//ベクトルとエネミーの長さの比較
		if (LENGTH > playerDirection)
		{
			//プレイヤーがエネミーの視野範囲内にいるならば
			if (radian <= dot)
			{
				(*itr)->PlayerFind(sub);
			}
		}
		else
		{
			(*itr)->PlayerReset();
		}
	}
}