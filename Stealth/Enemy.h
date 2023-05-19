#pragma once

#include "EnemyBase.h"
#include "Math3D.h"
#include "Collision.h"

/// <summary>
/// エネミークラス
/// </summary>
class Enemy final : public EnemyBase
{
public:
	Enemy(int movePattern, float enemySpeed);
	virtual ~Enemy();

	void Update(float deltaTime, VECTOR playerPosition);	//更新処理
	void Draw();											//描画処理

	void VisualAngleCake(float deltaTime, VECTOR bulletPosition);	//エネミーの視野にケーキが入った場合
	void Reaction();								//エネミーのオブジェクトごとの反応
	void HitPlayer();												//プレイヤーと衝突した

	const float GetCollideRadius() { return collisionSphere.radius; }	//当たり判定球の半径を返す
	const bool Spotted() { return playerSpotted; }						//プレイヤーを見つけたかどうかを返す
	const bool CakeFlag() { return cakeFlag; }							//ケーキを見つけたかどうかを返す

	//オブジェクトごとのエネミーの反応
	enum class EnemyReaction
	{
		NORMAL,		//見つけていない
		PLAYER,		//プレイヤー
		CAKE,		//ケーキ
	};

	EnemyReaction enemyReaction;		//オブジェクトごとのエネミーの反応

private:
	Enemy(const Enemy&);							//コピーコンストラクタ

	void Initialize();								//初期化処理
	void Finalize();								//終了処理
	void Move(float deltaTime);						//移動処理
	void Position(vector<VECTOR>& id);				//エネミー位置設定
	void StateUpdate(float deltaTime);				//エネミーの状態の変化
	void SetTargetPosition();						//目的地まで移動処理
	void VisualAnglePlayer(VECTOR playerPosition);	//エネミーの視野にプレイヤーが入った場合
	void CakeEatCount(float deltaTime);				//秒数によってケーキの状態変化
	void ReactionDraw();							//リアクション画像の描画処理
	void EnemyRotate(float deltaTime);				//エネミーの回転処理
	void EnemyRotateTime(float deltaTime);			//エネミーの回転の時間
	bool IsGoal(float deltaTime);					//目的地に到達したならば

	//エネミーの動き
	enum class EnemyState
	{
		CRAWL,		//巡回中
		ARRIVAL,	//目的地に到着
		ROTATION,	//方向転換
	};

	struct RotateTime
	{
		EnemyReaction enemyReaction;	//オブジェクトごとのエネミーの反応
		float time;						//各オブジェクトの回転時間
	};

	EnemyState enemyState;				//エネミーの動き

	My3dLib::Sphere collisionSphere;	//当たり判定球

	vector<VECTOR>::iterator itr;		//座標リストのイテレータ
	vector<VECTOR> positionList;		//エネミーの座標リスト

	float cakeCount;		//エネミーのケーキの反応カウント
	bool cakeFindFlag;		//エネミーがケーキを見つけたかどうか
	bool rotateFlag;		//回転させるかさせないか
	VECTOR nextDirection;	//回転したい向き
};