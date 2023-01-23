#pragma once

#include <string>
#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;

/// <summary>
/// エネミークラス
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(std::vector<VECTOR>& id);		//コンストラクタ
	 virtual ~Enemy();								//デストラクタ

	void Initialize();
	void Activate();
	void Update(float deltaTime, Player* player);
	void Draw();

	void VisualAngleBall(VECTOR bulletPos);			//視野角の計算
	void VisualAngleWall(VECTOR wallPos);

	bool Discovery() { return discovery; }
	int GetPlayerCount() { return playerFindCount; }
	
	//エネミーの状態
	enum class EnemyState
	{
		CRAWL,			//巡回中
		ARRIVAL,		//目的地に到着
	};

private:
	Enemy(const Enemy&);						//コピーコンストラクタ

	void Position(std::vector<VECTOR>& num);	//エネミー位置設定
	bool IsGoal(float deltaTime);				//目的地に到達したならば
	void eUpdate(float deltaTime);				//状態変化
	void SetTargetPosition();					//目的地まで移動処理
	void VisualAngle(Player* player);			//視野角の計算
	
	
	void Reaction();				//エネミーのオブジェクトごとの反応
	void Finalize();

	EnemyState enemyState;

	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	int visualModelHandle;
	VECTOR visualPosition;
	VECTOR visualDir;

	//静的定数
	static const std::string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const std::string SOUND_FOLDER_PATH;	//soundフォルダまでのパス
	static const std::string FIND_PATH;			//見つかった画像のパス
	static const std::string MARK_PATH;			//ビックリマーク画像のパス
	static const std::string DISCOVERY_SE_PATH;	//プレイヤー発見SE音のパス
};