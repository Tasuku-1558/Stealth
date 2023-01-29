#pragma once

#include <string>
#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;

/// <summary>
/// エネミークラス(赤色)
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(std::vector<VECTOR>& id);
	 virtual ~Enemy();

	void Initialize();									//初期化処理
	void Activate();									//活性化処理
	void Update(float deltaTime, Player* player);		//更新処理
	void Draw();										//描画処理

	void VisualAngleBall(Bullet* bullet);				//エネミーの視野にボールが入った場合
	void VisualAngleWall(VECTOR wallPos);				//エネミーの視野に壁が入った場合

	const bool Spotted() { return playerSpotted; }			//プレイヤーを見つけたかどうかを返す
	const bool BallFlag() { return ballFlag; }				//ボールを見つけたかどうかを返す
	const int GetPlayerCount() { return playerFindCount; }	//プレイヤーを見つけた回数を返す
	
	//エネミーの状態
	enum class EnemyState
	{
		CRAWL,			//巡回中
		ARRIVAL,		//目的地に到着
	};

private:
	Enemy(const Enemy&);						//コピーコンストラクタ

	void Position(std::vector<VECTOR>& id);		//エネミー位置設定
	bool IsGoal(float deltaTime);				//目的地に到達したならば
	void eUpdate(float deltaTime);				//エネミーの状態変化
	void SetTargetPosition();					//目的地まで移動処理
	void VisualAnglePlayer(Player* player);		//エネミーの視野にプレイヤーが入った場合
	
	void Reaction();							//エネミーのオブジェクトごとの反応
	void Finalize();							//終了処理

	EnemyState enemyState;						//エネミーの状態

	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	int count;
	//静的定数
	static const std::string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const std::string SOUND_FOLDER_PATH;	//soundフォルダまでのパス
	static const std::string FIND_PATH;			//見つかった画像のパス
	static const std::string MARK_PATH;			//ビックリマーク画像のパス
	static const std::string SPOTTED_SE_PATH;	//プレイヤー発見SE音のパス
};