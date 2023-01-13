#pragma once

#include <string>
#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"
#include "Map.h"
#include "SecondStageMap.h"
#include "Player.h"


/// <summary>
/// エネミーの状態
/// </summary>
enum class EnemyState
{
	CRAWL,			//巡回中
	ARRIVAL,		//目的地に到着
};


/// <summary>
/// エネミークラス
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(Map* map);		//コンストラクタ
	 Enemy(SecondStageMap* secondStageMap);
	~Enemy();				//デストラクタ

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void Draw();

	bool Discovery() { return discovery; }

	int GetPlayerCount() { return playerFindCount; }
	
	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);						//コピーコンストラクタ

	void Position(Map* map);					//エネミー位置設定
	void FirstPosition(SecondStageMap* secondStageMap);
	void SecondPosition(SecondStageMap* secondStageMap);
	bool IsGoal(float deltaTime);				//目的地に到達したならば
	void eUpdate(float deltaTime);				//状態変化
	void SetTargetPosition();					//移動処理
	void VisualAngle(Player* player);			//視野角の計算
	void VisualAngleBall(Player* player);			//視野角の計算
	void Reaction(Object object);				//エネミーのオブジェクトごとの反応
	void Finalize();


	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	

	//静的定数
	static const std::string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const std::string SOUND_FOLDER_PATH;	//soundフォルダまでのパス
	static const std::string FIND_PATH;			//見つかった画像のパス
	static const std::string VIEW_RANGE_PATH;
	static const std::string MARK_PATH;			//ビックリマーク画像のパス
	static const std::string DISCOVERY_SE_PATH;	//プレイヤー発見SE音のパス
};