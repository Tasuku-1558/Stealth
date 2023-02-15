#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Cake;

/// <summary>
/// 当たり判定クラス
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	 virtual ~HitChecker();

	void Check(int model, Player* player);					//衝突判定
	void BallAndPlayer(VECTOR playerPos, Cake* cake);		//ケーキとプレイヤーの当たり判定
	void EnemyAndPlayer(VECTOR playerPos, VECTOR enemyPos);	//エネミーとプレイヤーの当たり判定


	const bool CakeHit() { return cakeHit; }				//ケーキにプレイヤーが当たったかどうかを返す
	const bool EnemyHit() { return enemyHit; }				//エネミーにプレイヤーが当たったかどうかを返す
	const bool UI() { return uiDraw; }						//UI画像に当たったかどうかを返す
	const VECTOR Back() { return pushBack; }				//マップの壁にプレイヤーが衝突したときの押し戻し値を返す
	const bool MapHit() { return mapHit; }					//マップもプレイヤーが衝突したかどうかを返す

private:

	HitChecker(const HitChecker&);							//コピーコンストラクタ

	void PlayerAndUI(Player* player);						//プレイヤーとUI画像の当たり判定
	void MapAndPlayer(int model, Player* player);			//マップとプレイヤーの当たり判定


	bool cakeHit;			//ケーキに衝突したならば
	bool enemyHit;			//エネミーと衝突したならば
	VECTOR uiPosition;		//UI画像の位置
	bool uiDraw;			//UI画像を描画するかどうか

	bool mapHit;			//マップモデルに衝突したならば
	VECTOR pushBack;		//マップに衝突した時の押し戻し量

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

	//静的定数
	static const VECTOR UI_POSITION;	//UI画像の位置

};