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

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//エネミーの視野にケーキが入った場合
	void VisualAngleWall(VECTOR wallPos);					//エネミーの視野に壁が入った場合


	const bool Spotted() { return playerSpotted; }			//プレイヤーを見つけたかどうかを返す
	const bool CakeFlag() { return cakeFlag; }				//ケーキを見つけたかどうかを返す
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
	void ReactionDraw();						//リアクション画像の描画処理
	void Finalize();							//終了処理

	std::string InputPath(std::string folderPath, //画像、SEのパスを入力
						  std::string path);

	EnemyState enemyState;						//エネミーの状態

	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	float speedCount;		//エネミースピード変化カウント
	bool cakeFindFlag;		//エネミーがケーキを見つけたかどうか
	bool cakeEatFlag;		//エネミーがケーキに近づいて食べているかどうか

	//静的定数
	static const std::string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const std::string SOUND_FOLDER_PATH;	//soundフォルダまでのパス
	static const std::string PLAYER_FIND_PATH;	//プレイヤーを見つけた画像のパス
	static const std::string MARK_PATH;			//ビックリマーク画像のパス
	static const std::string CAKE_EAT_PATH;		//ケーキを食べている画像のパス
	static const std::string SPOTTED_SE_PATH;	//プレイヤー発見SE音のパス
};