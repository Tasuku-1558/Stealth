#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Enemy;
class Cake;
class GoalFlag;

/// <summary>
/// 当たり判定クラス
/// </summary>
class HitChecker final
{
public:
	HitChecker();
	virtual ~HitChecker();

	void Check(int model, Player* player, GoalFlag* goalFlag);	//衝突判定
	void CakeAndPlayer(Player* player, Cake* cake);			//ケーキとプレイヤーの当たり判定
	void EnemyAndPlayer(Player* player, Enemy* enemy);	//エネミーとプレイヤーの当たり判定


	const bool UI() { return uiHit; }						//UI画像に当たったかどうかを返す
	const bool MapHit() { return mapHit; }					//マップにプレイヤーが衝突したかどうかを返す
	const bool FlagHit() { return flagHit; }				//ゴール旗にプレイヤーが当たったかどうかを返す
	const VECTOR Back() { return pushBack; }				//マップの壁にプレイヤーが衝突したときの押し戻し値を返す

private:

	HitChecker(const HitChecker&);							//コピーコンストラクタ

	void PlayerAndUI(Player* player);						//プレイヤーとUI画像の当たり判定
	void MapAndPlayer(int model, Player* player);			//マップとプレイヤーの当たり判定
	void FlagAndPlayer(GoalFlag* goalFlag, Player* player);		//ゴール旗とプレイヤーの当たり判定


	VECTOR uiPosition;		//UI画像の位置
	bool uiHit;				//UI画像を描画するかどうか
	bool flagHit;			//ゴール旗に衝突したかどうか
	bool mapHit;			//マップモデルに衝突したかどうか
	VECTOR pushBack;		//マップに衝突した時の押し戻し量

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

	//定数
	const VECTOR UI_POSITION;	//UI画像の位置

};