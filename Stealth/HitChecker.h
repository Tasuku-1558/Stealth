#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;
class Cake;

namespace My3dLib
{
	//球体当たり判定
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void Move(const VECTOR& pos);

		VECTOR localCenter; //球体のローカル中心座標
		VECTOR worldCenter; //球体のワールド中心座標
		float  radius;      //球体の半径
	};

	//当たり判定の関数組み合わせ
	bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2);

}

/// <summary>
/// 当たり判定クラス
/// </summary>
class HitChecker final
{
public:
	HitChecker();
	virtual ~HitChecker();

	void Check(int model, Player* player, VECTOR flagPos);	//衝突判定
	void CakeAndPlayer(VECTOR playerPos, Cake* cake);		//ケーキとプレイヤーの当たり判定
	void EnemyAndPlayer(VECTOR playerPos, VECTOR enemyPos);	//エネミーとプレイヤーの当たり判定


	const bool CakeHit() { return cakeHit; }				//ケーキにプレイヤーが当たったかどうかを返す
	const bool EnemyHit() { return enemyHit; }				//エネミーにプレイヤーが当たったかどうかを返す
	const bool UI() { return uiDraw; }						//UI画像に当たったかどうかを返す
	const bool MapHit() { return mapHit; }					//マップにプレイヤーが衝突したかどうかを返す
	const bool FlagHit() { return flagHit; }				//ゴール旗にプレイヤーが当たったかどうかを返す
	const VECTOR Back() { return pushBack; }				//マップの壁にプレイヤーが衝突したときの押し戻し値を返す

private:

	HitChecker(const HitChecker&);							//コピーコンストラクタ

	void PlayerAndUI(Player* player);						//プレイヤーとUI画像の当たり判定
	void MapAndPlayer(int model, Player* player);			//マップとプレイヤーの当たり判定
	void FlagAndPlayer(VECTOR flagPos, Player* player);		//ゴール旗とプレイヤーの当たり判定


	bool cakeHit;			//ケーキに衝突したならば
	bool enemyHit;			//エネミーと衝突したならば
	VECTOR uiPosition;		//UI画像の位置
	bool uiDraw;			//UI画像を描画するかどうか
	bool flagHit;			//ゴール旗に衝突したならば

	bool mapHit;			//マップモデルに衝突したならば
	VECTOR pushBack;		//マップに衝突した時の押し戻し量

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

	//定数
	const VECTOR UI_POSITION;	//UI画像の位置

};