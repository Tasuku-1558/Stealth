#pragma once

#include <string>
#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;
class HitChecker;

using namespace std;

/// <summary>
/// エネミークラス(赤色)
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(vector<VECTOR>& id, float enemySpeed);
	 virtual ~Enemy();

	void Initialize();									//初期化処理
	void Activate();									//活性化処理
	void Update(float deltaTime, Player* player, HitChecker* hitChecker);		//更新処理
	void Draw();										//描画処理

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//エネミーの視野にケーキが入った場合

	const bool Spotted() { return playerSpotted; }			//プレイヤーを見つけたかどうかを返す
	const bool CakeFlag() { return cakeFlag; }				//ケーキを見つけたかどうかを返す

	//エネミーの状態
	enum class EnemyState
	{
		CRAWL,			//巡回中
		ARRIVAL,		//目的地に到着
		ROTATION,
	};

	//オブジェクトごとのエネミーの反応
	enum class EnemyReaction
	{
		PLAYER,
		CAKE,
	};

private:
	Enemy(const Enemy&);						//コピーコンストラクタ

	void Move(float deltaTime);					//移動処理
	void Position(vector<VECTOR>& id);			//エネミー位置設定
	bool IsGoal(float deltaTime);				//目的地に到達したならば
	void eUpdate(float deltaTime);				//エネミーの状態変化
	void SetTargetPosition();					//目的地まで移動処理
	void VisualAnglePlayer(Player* player);		//エネミーの視野にプレイヤーが入った場合
	
	void Reaction();							//エネミーのオブジェクトごとの反応
	void CakeEatCount(float deltaTime);			//秒数によってケーキの状態変化
	void ReactionDraw();						//リアクション画像の描画処理
	void Finalize();							//終了処理

	string InputPath(string folderPath,			//画像のパスを入力
					 string imagePath);

	EnemyState enemyState;						//エネミーの状態
	EnemyReaction enemyReaction;				//オブジェクトごとのエネミーの反応

	vector<VECTOR>::iterator itr;
	vector<VECTOR> pointList;

	float cakeCount;		//エネミーのケーキの反応カウント
	bool cakeFindFlag;		//エネミーがケーキを見つけたかどうか
	bool cakeEatFlag;		//エネミーがケーキに近づいて食べているかどうか
	bool cakeHalfFlag;		//ケーキが半分になっているかどうか


	//定数
	const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	const string MARK_PATH;			//ビックリマーク画像のパス
	const string CAKE_PATH;			//ケーキ画像のパス
	const string CAKE_HALF_PATH;	//ケーキが半分の画像のパス
};