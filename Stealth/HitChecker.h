#pragma once

#include <vector>
#include "DxLib.h"
#include "Math3D.h"

class Stage;
class Player;
class CakeBullet;
class Enemy;
class GoalFlag;

using namespace std;

/// <summary>
/// 当たり判定クラス
/// </summary>
class HitChecker final
{
public:
	HitChecker();
	virtual ~HitChecker();

	void Check(vector<Stage*>* stage, 
			   Player* player, 
			   vector<CakeBullet*>* cakeBullet, 
			  /* vector<Enemy*>* enemy, */
			   GoalFlag* goalFlag);				//衝突判定

	void EnemyAndPlayer(Player* player, /*vector<Enemy*>* enemy*/Enemy* enemy);	//エネミーとプレイヤーの当たり判定

	const bool UiHit() { return uiHit; }					//Ui画像に当たったかどうかを返す
	const bool FlagHit() { return flagHit; }				//ゴールオブジェクトにプレイヤーが当たったかどうかを返す
	const bool MapHit() { return mapHit; }					//マップにプレイヤーが衝突したかどうかを返す
	const VECTOR Back() { return pushBack; }				//マップの壁にプレイヤーが衝突したときの押し戻し値を返す

private:
	HitChecker(const HitChecker&);							//コピーコンストラクタ

	void CakeAndPlayer(Player* player, vector<CakeBullet*>* cakeBullet);	//ケーキとプレイヤーの当たり判定
	void PlayerAndUi(Player* player);										//プレイヤーとUi画像の当たり判定
	void MapAndPlayer(vector<Stage*>* stage, Player* player);				//マップとプレイヤーの当たり判定
	void FlagAndPlayer(GoalFlag* goalFlag, Player* player);					//ゴールオブジェクトとプレイヤーの当たり判定


	float moveLengh;		//移動量
	bool uiHit;				//Ui画像を描画するかどうか
	bool flagHit;			//ゴールオブジェクトに衝突したかどうか
	bool mapHit;			//マップモデルに衝突したかどうか
	VECTOR uiPosition;		//Ui画像の位置
	VECTOR pushBack;		//マップに衝突した時の押し戻し量
	VECTOR moveVec;			//移動ベクトル
	VECTOR planeNormal;		//ポリゴン平面法線

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;

	//定数
	const int	 FRAME_INDEX;	//当たり判定情報を更新するフレームの番号
	const int	 DIV_NUMBER;	//コリジョン情報の軸方向の空間分割数
	const float  SCALE;			//スケーリング値
	const VECTOR UI_POSITION;	//Ui画像の位置

};