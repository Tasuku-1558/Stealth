#pragma once

#include <string>

#include "EnemyBase.h"
#include "Math3D.h"
#include "Collision.h"

class Player;
class Bullet;

using namespace std;

/// <summary>
/// エネミークラス
/// </summary>
class Enemy final : public EnemyBase
{
public:
	Enemy(int number, float enemySpeed);
	virtual ~Enemy();

	void Update(float deltaTime, Player* player);		//更新処理
	void Draw();										//描画処理

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//エネミーの視野にケーキが入った場合
	void HitPlayer();										//プレイヤーと衝突した

	const float GetCollideRadius() { return collisionSphere.radius; }		//当たり判定球の半径を返す
	const bool Spotted() { return playerSpotted; }			//プレイヤーを見つけたかどうかを返す
	const bool CakeFlag() { return cakeFlag; }				//ケーキを見つけたかどうかを返す
	const bool CakeEatFlag() { return cakeEat; }

private:
	Enemy(const Enemy&);						//コピーコンストラクタ

	void Initialize();							//初期化処理
	void Finalize();							//終了処理
	void Move(float deltaTime);					//移動処理
	void Position(vector<VECTOR>& id);			//エネミー位置設定
	void StateUpdate(float deltaTime);			//エネミーの状態変化
	void SetTargetPosition();					//目的地まで移動処理
	void VisualAnglePlayer(Player* player);		//エネミーの視野にプレイヤーが入った場合
	void Reaction();							//エネミーのオブジェクトごとの反応
	void CakeEatCount(float deltaTime);			//秒数によってケーキの状態変化
	void ReactionDraw();						//リアクション画像の描画処理
	void EnemyRotate(float deltaTime);			//エネミーの回転処理
	bool IsGoal(float deltaTime);				//目的地に到達したならば

	string InputPath(string folderPath,			//画像のパスを入力
					 string imagePath);

	//エネミーの動き
	enum class EnemyState
	{
		CRAWL,			//巡回中
		ARRIVAL,		//目的地に到着
		ROTATION,		//方向転換
	};

	//オブジェクトごとのエネミーの反応
	enum class EnemyReaction
	{
		NORMAL,			//見つけていない
		PLAYER,			//プレイヤー
		CAKE,			//ケーキ
	};

	EnemyState enemyState;						//エネミーの動き
	EnemyReaction enemyReaction;				//オブジェクトごとのエネミーの反応

	My3dLib::Sphere collisionSphere;			//当たり判定球

	vector<VECTOR>::iterator itr;
	vector<VECTOR> pointList;

	float cakeCount;		//エネミーのケーキの反応カウント
	bool cakeFindFlag;		//エネミーがケーキを見つけたかどうか

	VECTOR nextDirection;	//回転したい向き
	bool rotateFlag;		//回転させるかさせないか
	float frame;
	bool cakeEat;

	//定数
	const string IMAGE_FOLDER_PATH;	//Imageフォルダまでのパス
	const string MARK_PATH;			//ビックリマーク画像のパス
};